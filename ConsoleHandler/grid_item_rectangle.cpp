#include "stdafx.h"
#include "grid_item_rectangle.h"
#include "console_utils.h"
#include "console_output.h"

namespace console_handler
{
  grid_item_rectangle::grid_item_rectangle(const console_handler::grid_item& menu_item,
                                           const shape_rectangle& item_rectangle, const int menu_row,
                                           const int menu_row_index)
    : grid_item(menu_item), item_rectangle(item_rectangle),
      grid_row(menu_row), grid_row_index(menu_row_index)
  {
  }

  void grid_item_rectangle::draw_border() const
  {
      // calculate box properties
      const int item_height = (item_rectangle.get_right().Y - item_rectangle.get_left().Y);
      const int item_width = (item_rectangle.get_right().X - item_rectangle.get_left().X);

      std::string top_bottom_line = grid_item.border_color_code;
      std::string border_left_right = grid_item.border_color_code;
      for (int i = 0; i <= item_width; i++)
        top_bottom_line += grid_item.border_char;

      for (int i = 0; i <= grid_item.border_size; i++)
        border_left_right += grid_item.border_char;

      // draw border
      for (int height = 0; height <= item_height; height++)
      {
        console_utils::set_console_cursor_pos({
          short(item_rectangle.get_left().X),
          short(item_rectangle.get_left().Y + short(height))
          });

        for (int width = 0; width <= item_width; width++)
        {
          if (height <= grid_item.border_size || height >= item_height - grid_item.border_size)
          {
            console_output::print(top_bottom_line);
            break;
          }
          if (width == 0 || width == item_width - grid_item.border_size)
          {
            console_utils::set_console_cursor_pos(
              { item_rectangle.get_left().X + short(width), item_rectangle.get_left().Y + short(height) });
            console_output::print(border_left_right);
          }
        }
      }
  }
}
