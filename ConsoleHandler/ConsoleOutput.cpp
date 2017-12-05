#include "stdafx.h"
#include "ConsoleOutput.h"
#include "ConsoleUtils.h"
#include "ConsoleTypes.h"
#include <string.h>

namespace console_handler
{
  /**
   * \brief Prints a line with the given text.
   * \brief Cuts the line in sub lines if the text is to long
   * \param message The message wich should be written to the console
   */
  void ConsoleOutput::print(console_types console_type, std::string message)
  {
    std::string consoleTypeText = console_utils::get_console_type_text(console_type);
    std::string out_message = consoleTypeText + " | " + message;
    printf("%s\n", out_message.c_str());
  }

  /**
   * \brief Prints a line the console
   * \param pattern The pattern for the line. Default = 
   */
  void ConsoleOutput::print_line(const console_types console_type, std::string pattern)
  {
    int console_witdh = console_utils::get_console_width();
    console_witdh -= console_utils::get_console_type_text(console_type).length() - 3;
    std::string print_str = "";

    for(int i = 0; i < console_witdh / pattern.length(); i++)
    {
      print_str += pattern;
    }
    print(console_type, "\n" + print_str);
  }
}
