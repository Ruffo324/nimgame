#include "stdafx.h"
#include "ascii_block_list.h"
#include "console_utils.h"

namespace console_handler
{
  ascii_block_list::ascii_block_list(const std::string string_value, const int font_size_value, const COLOR_STRUCT foreground_color_value)
    : original_string(string_value), font_size(font_size_value),  foreground_color(foreground_color_value)
  {
    for (int i = 0; i < original_string.length(); i++)
      ascii_blocks.push_back(ascii_block(original_string[i], font_size, foreground_color));
  }

  void ascii_block_list::print()
  {
    const COORD current_cursor_position = console_utils::get_console_cursor_position();
    for (int i = 0; i < ascii_blocks.size(); i++)
    {
      console_utils::set_console_cursor_pos({
        current_cursor_position.X + short((font_size * i)),
        current_cursor_position.Y
      });
      ascii_blocks[i].print();
    }
  }
}
