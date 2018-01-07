#include "stdafx.h"
#include "ascii_block_list.h"
#include "console_utils.h"
#include <iostream>
#include <conio.h>
#include <cctype>

namespace console_handler
{
  ascii_block_list::ascii_block_list(const std::string string_value, const int font_size_value,
    const COLOR_STRUCT foreground_color_value)
    : original_string(string_value), font_size(font_size_value), foreground_color(foreground_color_value)
  {
    create_blocks();
  }

  ascii_block_list::ascii_block_list(const std::string string_value, const int font_size_value)
    : original_string(string_value), font_size(font_size_value)

  {
    create_blocks();
  }

  ascii_block_list::ascii_block_list(const int font_size_value)
    : font_size(font_size_value), center_(false), item_side_length_(0)

  {
  }

  void ascii_block_list::center_block_list(const bool center, const int item_side_length)
  {
    center_ = center;
    item_side_length_ = item_side_length;
  }

  void ascii_block_list::draw()
  {
    const COORD current_cursor_position = console_utils::get_console_cursor_position();
    const short offset_center = center_
      ? short(((item_side_length_ - int(font_size / 2) * ascii_blocks.size()) / 2))
      : 0;
    for (int i = 0; i < ascii_blocks.size(); i++)
    {
      console_utils::set_console_cursor_pos({
        (current_cursor_position.X + short((int(font_size / 2) * i))) + offset_center,
        current_cursor_position.Y
        });
      ascii_blocks[i].draw();
    }
  }

  void ascii_block_list::input(std::string background_color_string)
  {
    // draw an ">" to declare user input
    _COORD start_pos = console_utils::get_console_cursor_position();
    ascii_block input_hint_char = ascii_block('>', font_size, COLOR_STRUCT("#424242"));
    input_hint_char.draw();
    console_utils::set_console_cursor_pos({ start_pos.X + short(input_hint_char.ascii_block_size.cx / 2), start_pos.Y });

    // User input
    std::string input = "";
    char input_char = char(0);

    // Get input until enter
    while (input_char != '\r' || input.size() == 0)
    {
      _COORD console_pos = console_utils::get_console_cursor_position();
      input_char = _getch();
      if (input_char != '\r')
      {
        // Backspace
        if (input_char == '\b')
        {
          if (input.length() > 0)
          {
            const char removed_char = input.substr(input.length() - 1).c_str()[0];
            input = input.substr(0, input.length() - 1);
            ascii_block char_new = ascii_block(removed_char, font_size, COLOR_STRUCT(background_color_string));
            console_utils::set_console_cursor_pos({
              console_pos.X - short(char_new.ascii_block_size.cx / 2) , console_pos.Y
              });
            char_new.draw();
            console_utils::set_console_cursor_pos({
              console_pos.X - short(char_new.ascii_block_size.cx / 2) , console_pos.Y
              });
          }
        }
        else
        {
          // Only alphanumeric chars and max length of 15.
          if (isalnum(static_cast<unsigned char>(input_char)) && input.length() < 15)
          {
            ascii_block char_new = ascii_block(input_char, font_size, COLOR_STRUCT(0, 0, 0));
            char_new.draw();
            input += input_char;
            console_utils::set_console_cursor_pos({
              console_pos.X + short(char_new.ascii_block_size.cx / 2) , console_pos.Y
              });
          }
        }
      }
    }

    original_string = input;
  }

  void ascii_block_list::create_blocks()
  {
    bool color_code_parsing = false;
    std::string current_parsing_color_code = "";

    // Parse chars and color_codes
    for (int i = 0; i < original_string.length(); i++)
    {
      if (color_code_parsing)
      {
        if (original_string[i] == '}')
        {
          color_code_parsing = false;
          foreground_color = COLOR_STRUCT(current_parsing_color_code);
          current_parsing_color_code = "";
          continue;
        }

        current_parsing_color_code += original_string[i];
        continue;
      }

      if (original_string[i] == '{')
      {
        color_code_parsing = true;
        continue;
      }

      ascii_blocks.push_back(ascii_block(original_string[i], font_size, foreground_color));
    }
  }
}
