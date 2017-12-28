#pragma once
#include "COLOR_STRUCT.h"
#include <string>
#include "console_handler.h"

namespace console_handler
{
  class CONSOLE_HANDLER_API console_color
  {
  public:
    static std::string parse_string_to_ansi_string(std::string message);
    static std::string color_code_to_ansi(std::string color_code, COLOR_STRUCT
                                          last_color_struct);
    static std::string color_struct_to_ansi(COLOR_STRUCT color_struct, COLOR_STRUCT last_color_struct, bool background);
  };
}
