#pragma once
#include "COLOR_STRUCT.h"
#include <string>
#include "console_handler.h"

namespace console_handler
{
  class console_color
  {
  public:
    static CONSOLE_HANDLER_API std::string parse_string_to_ascii_string(std::string message);
    static CONSOLE_HANDLER_API std::string color_code_to_ascii(std::string color_code, COLOR_STRUCT
                                           last_color_struct);
  private:
    static COLOR_STRUCT color_code_to_struct(std::string color_code);
  };
}
