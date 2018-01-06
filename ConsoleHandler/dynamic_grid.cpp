#include "stdafx.h"
#include "dynamic_grid.h"
#include "console_utils.h"
#include "COLOR_STRUCT.h"
#include "ascii_block_list.h"
#include "console_color.h"
#include <conio.h>

namespace console_handler
{
  void dynamic_grid::draw_item(grid_item_rectangle item) const
  {
    // print rectangle background
    item.item_rectangle.print();


    //TODO: add innerbox padding
    const int offset = item.grid_item.border_size + 10;

    // Calculate text width
    int text_width = 0;
    if (item.grid_item.caption != "")
    {
      text_width = int(round((item_side_length_ - (offset * 2)) / (longest_caption_length_)));

      // print text
      console_utils::set_console_cursor_pos({
        item.item_rectangle.get_left().X + short(item.grid_item.border_size * 2),
        item.item_rectangle.get_right().Y - short(text_width + item.grid_item.border_size * 2)
        });
      ascii_block_list caption_blocks = ascii_block_list(item.grid_item.caption, text_width);
      caption_blocks.center_block_list(true, item_side_length_ - offset * 2);
      caption_blocks.draw();
    }

    //print icon
    console_utils::set_console_cursor_pos({
      item.item_rectangle.get_left().X + short(offset),
      item.item_rectangle.get_left().Y + short(offset)
      });
    const SIZE icon_size = {
      item_side_length_ - ((offset * 2) + text_width * 2),
      item_side_length_ - ((offset * 2) + text_width * 2)
    };

    ascii_block icon_block = ascii_block(item.grid_item.icon_file, icon_size,
      COLOR_STRUCT(item.grid_item.selected
        ? item.grid_item.selected_icon_foreground_color_code
        : item.grid_item.icon_foreground_color_code));
    icon_block.add_padding(text_width);
    icon_block.draw();
  }

  void dynamic_grid::draw()
  {
    // draw boxes
    for (int i = 0; i < items_.size(); i++)
    {
      // Item is not visible -> skip
      if (!items_[i].grid_item.visible)
        continue;

      draw_item(items_[i]);
    }
  }

  int dynamic_grid::select()
  {
    return select(true, false);
  }

  int dynamic_grid::select(const bool run_item_action, const bool space_forces_return,
    const std::function<void()> optional_enter_action, const bool row_lock, const int start_index)
  {
    int current_selected_index = start_index;
    int last_selected_index = -1;
    char input = 0;
    bool was_arrow_key = false;
    bool was_enter = false;

    // until enter
    while (input != '\r' && (space_forces_return && input != ' ') || current_selected_index == -1)
    {
      if (last_selected_index != current_selected_index)
      {
        // redraw last
        if (last_selected_index != -1)
        {
          const std::string original_background = items_[last_selected_index].grid_item.border_color_code;
          items_[last_selected_index].grid_item.border_color_code = items_[last_selected_index].grid_item.selected
            ? items_[last_selected_index].grid_item.selected_color_background
            : items_[last_selected_index].grid_item.item_background;
          items_[last_selected_index].draw_border();
          items_[last_selected_index].grid_item.border_color_code = original_background;
        }

        const grid_item_rectangle current_item = items_[current_selected_index];

        // draw border
        current_item.draw_border();
      }

      input = _getch();
      if (input == -32)
      {
        was_arrow_key = true;
        continue;
      }
      // remind last index
      last_selected_index = current_selected_index;

      if (was_arrow_key)
        switch (input)
        {
          //  arrow rigth
        case 'M':
          do
          {
            current_selected_index++;
            if (current_selected_index + 1 > int(items_.size()))
            {
              current_selected_index = 0;
              while (items_[current_selected_index].grid_item.disabled)
                current_selected_index++;
            }
          } while (items_[current_selected_index].grid_item.disabled);
          break;
          //  arrow left
        case 'K':
          do
          {
            current_selected_index--;
            if (current_selected_index < 0)
            {
              current_selected_index = items_.size() - 1;
              while (items_[current_selected_index].grid_item.disabled)
                current_selected_index--;
            }
          } while (items_[current_selected_index].grid_item.disabled);
          break;
          //  arrow up
        case 'H':

          current_selected_index -= boxes_per_row_;

          if (current_selected_index < 0)
            current_selected_index = items_.size() - abs(current_selected_index);

          while (items_[current_selected_index].grid_item.disabled)
            current_selected_index--;
          break;
          //  arrow down
        case 'P':
          current_selected_index += boxes_per_row_;

          if (current_selected_index >= items_.size())
          {
            current_selected_index -= boxes_per_row_;
            current_selected_index = current_selected_index % boxes_per_row_;
            while (items_[current_selected_index].grid_item.disabled)
            {
              current_selected_index--;
              if (current_selected_index < 0)
                current_selected_index = items_.size() - 1;
            }
          }
          else
          {
            while (items_[current_selected_index].grid_item.disabled)
            {
              current_selected_index++;
              if (current_selected_index + 1 > int(items_.size()))
              {
                current_selected_index = 0;
              }
            }
          }
          break;
        default:
          //TODO: Hint with wrong key
          break;
        }

      // Reset index if row lock active and row changed
      if (row_lock)
      {
        if (items_[current_selected_index].grid_row != items_[last_selected_index].grid_row)
          current_selected_index = last_selected_index;
      }

      was_arrow_key = false;
    }


    was_enter = input == '\r';

    // Eval grid item function
    if (current_selected_index != -1 && run_item_action && was_enter)
      items_[current_selected_index].grid_item.run();

    // Eval optional function if given
    if (optional_enter_action != nullptr && current_selected_index != -1 && was_enter)
      optional_enter_action();


    return current_selected_index;
  }

  std::vector<int> dynamic_grid::mark_and_select(const bool row_lock, const int max_items,
    const std::string select_color, const std::string selected_color_icon)
  {
    std::vector<int> selected_indexes;
    bool confirmed = false;
    int last_index = -1;

    do
    {
      int selected = select(false, true, [confirmed]() mutable -> void { confirmed = true; },
        row_lock && selected_indexes.size() > 0, last_index);
      // Contains? -> unmark
      if (find(selected_indexes.begin(), selected_indexes.end(), selected) != selected_indexes.end())
      {
        const std::vector<int>::iterator position = find(selected_indexes.begin(), selected_indexes.end(), selected);
        selected_indexes.erase(position);

        // unmark
        items_[selected].grid_item.selected = false;
        items_[selected].item_rectangle.change_color_string(items_[selected].grid_item.item_background);
        draw_item(items_[selected]);
      }
      else
      {
        selected_indexes.push_back(selected);

        // mark
        items_[selected].grid_item.selected_color_background = select_color;
        items_[selected].grid_item.selected_icon_foreground_color_code = selected_color_icon;
        items_[selected].grid_item.selected = true;
        items_[selected].item_rectangle.change_color_string(select_color);
        draw_item(items_[selected]);
      }

      last_index = selected;

      // Selected all in row -> confirmed
      if (row_lock)
      {
        confirmed = true;
        for (int i = 0; i < items_.size(); i++)
          if (items_[i].grid_row == items_[selected].grid_row
            && !items_[i].grid_item.selected
            && !items_[i].grid_item.disabled)
          {
            confirmed = false;
            break;
          }
      }

    } while (selected_indexes.size() == 0 || !confirmed && selected_indexes.size() < max_items);

    // unselect items
    for(int i = 0; i < selected_indexes.size(); i++)
      items_[i].grid_item.selected = false;

    return selected_indexes;
  }

  void dynamic_grid::set_size_multiplicator(const double multiplicator)
  {
    size_multiplicator_ = multiplicator;
  }

  void dynamic_grid::recalculate_item_size()
  {
    auto_sized_grid_init();
  }

  void dynamic_grid::disable_item(const int index, const std::string disabled_background_color, const std::string disabled_icon_color)
  {
    items_[index].grid_item.disabled = true;
    items_[index].grid_item.icon_foreground_color_code = disabled_icon_color;
    items_[index].grid_item.item_background = disabled_background_color;
    items_[index].item_rectangle.change_color_string(disabled_background_color);

    draw_item(items_[index]);
  }


  int dynamic_grid::calculate_side_length_automatic() const
  {
    int console_height = (console_utils::get_console_height() - (window_margin_ * 2)) - caption_top_offset_;
    int console_width = console_utils::get_console_width() - (window_margin_ * 2);
    const int smalles_window_length = min(console_height, console_width);

    int side_length = smalles_window_length / int(menu_items_.size());
    side_length = int(round(double(side_length) * size_multiplicator_));


    for (int i = smalles_window_length; i > 5; i--)
    {
      const int calculated_side_length = int(round(double(i) * size_multiplicator_));
      const int boxes_per_row = calculate_boxes_per_row(calculated_side_length);
      if (boxes_per_row > 1)
      {
        if (menu_items_.size() % 2 == 0)
        {
          if (menu_items_.size() % boxes_per_row == 0)
            return calculated_side_length;
        }
        else
          return calculated_side_length;
      }
    }

    return side_length;
  }

  int dynamic_grid::calculate_side_length(const int items_per_row) const
  {
    int console_height = (console_utils::get_console_height() - (window_margin_ * 2)) - caption_top_offset_;
    int console_width = console_utils::get_console_width() - (window_margin_ * 2);
    const int smalles_window_length = min(console_height, console_width);

    return (smalles_window_length - ((items_per_row * margin_between_boxes_) - margin_between_boxes_)) / (items_per_row
      );
  }

  int dynamic_grid::calculate_boxes_per_row(const int item_side_lenght) const
  {
    int console_height = (console_utils::get_console_height() - (window_margin_ * 2)) - caption_top_offset_;
    int console_width = console_utils::get_console_width() - (window_margin_ * 2);
    const int smalles_window_length = min(console_height, console_width);

    int max_per_row = -1;
    for (int i = 1; i < menu_items_.size() + 1; i++)
    {
      if ((((item_side_lenght + margin_between_boxes_) * i) - margin_between_boxes_) < console_width)
        if ((((item_side_lenght + margin_between_boxes_) * ceil(double(menu_items_.size()) / double(i))) -
          margin_between_boxes_) < console_height)
          max_per_row = i;
    }

    return max_per_row;
  }

  void dynamic_grid::calculate_rectangles()
  {
    items_.clear();
    int current_row = 0;
    int current_row_index = 0;

    // calculate rectangles
    for (int i = 0; i < menu_items_.size(); i++)
    {
      // rectangle left & right
      const _COORD left = {
        short(window_margin_ + current_row_index * item_side_length_ + current_row_index * margin_between_boxes_),
        short(window_margin_ + caption_top_offset_ + current_row * item_side_length_ + current_row *
          margin_between_boxes_)
      };

      // rectangle shape
      const shape_rectangle shape =
        shape_rectangle(left,
          {
            // right
            left.X + short(item_side_length_),
            left.Y + short(item_side_length_)
          },
          menu_items_[i].item_background, ' ');
      // add to items
      items_.push_back(grid_item_rectangle(menu_items_[i], shape, current_row, current_row_index));

      // next row index & next row
      current_row_index++;

      if ((i + 1) % boxes_per_row_ == 0)
      {
        current_row++;
        current_row_index = 0;
      }
    }


    // Get longest caption
    for (int i = 0; i < int(menu_items_.size()); i++)
      if (console_color::clean_string(menu_items_[i].caption).length() > longest_caption_length_)
        longest_caption_length_ = int(console_color::clean_string(menu_items_[i].caption).length());
  }

  void dynamic_grid::draw_caption() const
  {
    ascii_block_list caption = ascii_block_list(caption_, caption_font_size_);
    caption.center_block_list(true, console_utils::get_console_width() - (window_margin_ * 2));
    console_utils::set_console_cursor_pos({ short(window_margin_), short(window_margin_) });
    caption.draw();
  }

  void dynamic_grid::auto_sized_grid_init()
  {
    item_side_length_ = calculate_side_length_automatic();
    boxes_per_row_ = calculate_boxes_per_row(item_side_length_);
    calculate_rectangles();
  }

  dynamic_grid::dynamic_grid(const std::vector<grid_item> menu_items, const int window_margin,
    const int margin_between_boxes)
    : menu_items_(menu_items), window_margin_(window_margin), margin_between_boxes_(margin_between_boxes), caption_(""),
    caption_font_size_(0), caption_top_offset_(0)
  {
    auto_sized_grid_init();
  }

  dynamic_grid::dynamic_grid(const std::string grid_caption, const int caption_font_size,
    const std::vector<grid_item> menu_items, const int window_margin,
    const int margin_between_boxes)
    : menu_items_(menu_items), window_margin_(window_margin), margin_between_boxes_(margin_between_boxes),
    caption_(grid_caption), caption_font_size_(int(console_utils::get_console_height() / 300) * caption_font_size),
    caption_top_offset_(caption_font_size_)
  {
    draw_caption();
    auto_sized_grid_init();
  }

  dynamic_grid::dynamic_grid(const std::string grid_caption, const int caption_font_size,
    const std::vector<grid_item> menu_items, const int window_margin,
    const int margin_between_boxes, const int boxes_per_row)
    : menu_items_(menu_items), boxes_per_row_(boxes_per_row), window_margin_(window_margin),
    margin_between_boxes_(margin_between_boxes), caption_(grid_caption),
    caption_font_size_(int(console_utils::get_console_height() / 300) * caption_font_size),
    caption_top_offset_(caption_font_size_)
  {
    draw_caption();
    item_side_length_ = calculate_side_length(boxes_per_row_);
    calculate_rectangles();
  }

  dynamic_grid::dynamic_grid()
  {
  }

  bool dynamic_grid::all_items_disabled()
  {
    for(int i = 0; i < items_.size(); i++)
      if(!items_[i].grid_item.disabled)
        return false;

    return true;
  }
}
