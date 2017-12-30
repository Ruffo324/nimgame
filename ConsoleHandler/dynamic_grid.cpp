#include "stdafx.h"
#include "dynamic_grid.h"
#include "console_utils.h"
#include "COLOR_STRUCT.h"
#include "ascii_block_list.h"

namespace console_handler
{
  void dynamic_grid::draw()
  {
    // draw boxes
    for (int i = 0; i < items_.size(); i++)
    {
      // print rectangle background
      items_[i].item_rectangle.print();


      //TODO: add innerbox padding
      const int offset = items_[i].grid_item.border_size + 10;
      const int text_width =
        int(round((item_side_length_ - (offset * 2)) / (items_[i].grid_item.caption.length() / 2)));

      // print text
      console_utils::set_console_cursor_pos({
        items_[i].item_rectangle.get_left().X + short(items_[i].grid_item.border_size * 2),
        items_[i].item_rectangle.get_right().Y - short(text_width + items_[i].grid_item.border_size * 2)
      });
      ascii_block_list caption_blocks = ascii_block_list(items_[i].grid_item.caption, text_width,
                                                         COLOR_STRUCT(
                                                           items_[i].grid_item.caption_foreground_color_code));
      caption_blocks.center_block_list(true, item_side_length_ - offset * 2);
      caption_blocks.draw();


      //print icon
      console_utils::set_console_cursor_pos({
        items_[i].item_rectangle.get_left().X + short(offset),
        items_[i].item_rectangle.get_left().Y + short(offset)
      });
      const SIZE icon_size = {
        item_side_length_ - ((offset * 2) + text_width),
        item_side_length_ - ((offset * 2) + text_width)
      };

      ascii_block icon_block = ascii_block("../Icons/Settings.bmp", icon_size,
                  COLOR_STRUCT(items_[i].grid_item.icon_foreground_color_code));
      icon_block.add_padding(text_width);
      icon_block.draw();
    }
  }

  void dynamic_grid::select()
  {
  }


  int dynamic_grid::calculate_side_length_automatic() const
  {
    int console_height = (console_utils::get_console_height() - (window_margin_ * 2)) - caption_top_offset_;
    int console_width = console_utils::get_console_width() - (window_margin_ * 2);
    const int smalles_window_length = min(console_height, console_width);

    int max_per_row = 0;
    const int side_length = smalles_window_length / int(menu_items_.size());

    for (int i = smalles_window_length; i > 5; i--)
    {
      const int boxes_per_row = calculate_boxes_per_row(i);
      if (boxes_per_row > 1)
        return i;
    }

    return side_length;
  }

  int dynamic_grid::calculate_boxes_per_row(const int item_side_lenght) const
  {
    int console_height = (console_utils::get_console_height() - (window_margin_ * 2)) - caption_top_offset_;
    int console_width = console_utils::get_console_width() - (window_margin_ * 2);
    const int smalles_window_length = min(console_height, console_width);

    int max_per_row = -1;
    for (int i = 1; i < menu_items_.size(); i++)
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
        short(window_margin_ + caption_top_offset_ + current_row * item_side_length_ + current_row * margin_between_boxes_)
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
  }

  void dynamic_grid::draw_caption() const
  {
    ascii_block_list caption = ascii_block_list(caption_, caption_font_size_);
    caption.center_block_list(true, console_utils::get_console_width() - (window_margin_ * 2));
    console_utils::set_console_cursor_pos({short(window_margin_), short(window_margin_)});
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
      caption_(grid_caption), caption_font_size_((console_utils::get_console_height() / 300) * caption_font_size), caption_top_offset_(caption_font_size_)
  {
    draw_caption();
    auto_sized_grid_init();
  }
}
