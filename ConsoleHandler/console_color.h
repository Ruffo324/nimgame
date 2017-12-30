#pragma once
#include "COLOR_STRUCT.h"
#include <string>
#include "console_handler.h"
#include <map>

namespace console_handler
{
  class console_color
  {
  public:
    static CONSOLE_HANDLER_API std::string parse_string_to_ansi_string(std::string message);
    static CONSOLE_HANDLER_API std::string color_code_to_ansi(std::string color_code, COLOR_STRUCT
                                          last_color_struct);
    static CONSOLE_HANDLER_API std::string color_struct_to_ansi(COLOR_STRUCT color_struct, COLOR_STRUCT last_color_struct, bool background);
  private:
    static std::map<std::string, std::string> cached_translations_;
  };
}
