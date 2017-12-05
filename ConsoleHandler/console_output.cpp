#include "stdafx.h"
#include "console_output.h"
#include "console_utils.h"
#include "console_type.h"
#include "console_color.h"

namespace console_handler
{
  /**
   * \brief Prints a line with the given text.
   * \brief Cuts the line in sub lines if the text is to long
   * \param message The message wich should be written to the console
   */
  void console_output::print(const console_type type, const std::string message)
  {
    const std::string console_type_text = console_utils::get_console_type_text(type);
    std::string out_message = "{#ffffff}" + console_type_text + " | " + message + "{;}";

    out_message = console_color::parse_string_to_ascii_string(out_message);
    printf("%s\n", out_message.c_str());
  }

  /**
   * \brief Prints a line the console
   * \param pattern The pattern for the line. Default = 
   */
  void console_output::print_line(const console_type type, std::string pattern)
  {
    int console_witdh = console_utils::get_console_width();
    console_witdh -= console_utils::get_console_type_text(type).length() - 3;
    std::string print_str = "";

    for (unsigned int i = 0; i < console_witdh / pattern.length(); i++)
      print_str += pattern;

    print(type, "\n" + print_str);
  }
}
