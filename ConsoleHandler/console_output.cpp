#include "stdafx.h"
#include "console_output.h"
#include "console_utils.h"
#include "console_color.h"
#include <Windows.h>

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
    std::string out_message = "{;}{#ffffff}" + message;

    out_message = console_color::parse_string_to_ascii_string(out_message);
    printf("%s", out_message.c_str());
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
    std::string out_message = "{;}{#ffffff}" + message;

    out_message = console_color::parse_string_to_ascii_string(out_message);
    printf("%s\n", out_message.c_str());
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

  void console_output::print_rectangle(const SHAPE_RECTANGLE rectangle, std::string color_string)
  {
    const _COORD old_cursor_position = console_utils::get_console_cursor_position();

    // calculate recangle props
    const int lenght = rectangle.right.X - rectangle.left.X;
    const int height = rectangle.left.Y > rectangle.right.Y ? rectangle.left.Y - rectangle.right.Y : rectangle.right.Y - rectangle.left.Y;

    // calculate rectangle length
    std::string length_pattern = "";
    for (int i = 0; i < lenght; i++)
      length_pattern += " ";

    // add color code braces if not given
    if (color_string.front() != '{')
      color_string = '{' + color_string;
    if (color_string.back() != '}')
      color_string += '}';

    // print rectangle
    for(int i = 0; i < height; i++)
    {
      console_utils::set_console_cursor_pos({ rectangle.left.X, rectangle.left.Y + short(i)});
      print(color_string + length_pattern);
    }

    // reset to last cursor position
    console_utils::set_console_cursor_pos(old_cursor_position);
    print("");
  }
}
