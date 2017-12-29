#include "stdafx.h"
#include "console_output.h"
#include "console_utils.h"
#include "console_color.h"
#include <Windows.h>
#include <vector>
#include "menu_item_rectangle.h"
#include "console_ascii.h"
#include "ascii_block_list.h"

namespace console_handler
{
  /**
   * \brief Prints the given text to the console.
   * \brief Parsing color codes to ansii color codes
   * \brief Cuts the line in sub lines if the text is to long
   * \param message The message wich should be written to the console
   */
  void console_output::print(const std::string message)
  {
    std::string out_message = message;

    out_message = console_color::parse_string_to_ansi_string(out_message);
    internal_write(out_message);
  }

  /**
   * \brief Resets the color at the cursor position
   */
  void console_output::reset_color()
  {
    print("{;}");
  }

  /**
  * \brief Prints the given text to the console with new line feed.
  * \brief Parsing color codes to ansii color codes
  * \brief Cuts the line in sub lines if the text is to long
  * \param message The message wich should be written to the console
  */
  void console_output::print_line(const std::string message)
  {
    std::string out_message = "{;}" + message;

    out_message = console_color::parse_string_to_ansi_string(out_message);
    internal_write(out_message + "\n");
    //printf("%s\n", out_message.c_str());
  }

  /**
   * \brief Prints a line the console
   * \param pattern The pattern for the line. Default = 
   */
  void console_output::print_separatorline(std::string pattern)
  {
    const int console_witdh = console_utils::get_console_width();
    std::string print_str = "";

    for (unsigned int i = 0; i < console_witdh / pattern.length(); i++)
      print_str += pattern;

    const _COORD cursor_pos = console_utils::get_console_cursor_position();

    if (cursor_pos.X != 0)
      print_str = "\n" + print_str;

    print_line(print_str);
  }

  void console_output::fill_background(const std::string color_string, const char text_char)
  {
    console_utils::set_console_cursor_pos({0,0});
    const int console_height = console_utils::get_console_height();
    const int console_width = console_utils::get_console_width();

    std::string line = color_string;
    for (int i = 0; i < console_width; i++)
      line += text_char;

    // fill background
    for (int i = 0; i < console_height; i++)
      print_line(line);
  }


  void console_output::internal_write(std::string message)
  {
    const std::string reset_ansi_string = "\x1B[0m";
    const std::string ansi_start_string = "\x1B[";
    // save cursor position
    _COORD current_cursor = console_utils::get_console_cursor_position();
    std::string print_string = "";
    bool reset_active = false;

    for (int i = 0; i < message.length(); i++)
    {
      print_string += message[i];
      if (reset_active && print_string.length() >= ansi_start_string.length())
        if (print_string.substr(print_string.length() - ansi_start_string.length()) == ansi_start_string)
        {
          const int cursor_steps = int(print_string.length() - ansi_start_string.length());
          console_utils::set_console_cursor_pos({current_cursor.X + short(cursor_steps), current_cursor.Y});
          print_string = ansi_start_string;
          reset_active = false;
        }

      if (print_string.length() >= reset_ansi_string.length())
        if (print_string.substr(print_string.length() - reset_ansi_string.length()) == reset_ansi_string)
        {
          reset_active = true;
          print_string = print_string.substr(0, print_string.length() - reset_ansi_string.length());
          printf("%s", print_string.c_str());
          _flushall();
          current_cursor = console_utils::get_console_cursor_position();
          print_string = "";
        }
    }

    // print rest
    if (!reset_active && print_string.length() > 0)
    {
      printf("%s", print_string.c_str());
      _flushall();
    }
  }
}
