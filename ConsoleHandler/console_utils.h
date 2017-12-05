#pragma once
#include "console_handler.h"
#include <Windows.h>
#include <string>
#include "console_type.h"

namespace console_handler
{
  class console_utils
  {
  public:
    // Console base functions
    static CONSOLE_HANDLER_API HANDLE get_console_handler();
    static CONSOLE_HANDLER_API int get_console_width();
    static CONSOLE_HANDLER_API int get_console_height();
    static CONSOLE_HANDLER_API std::string get_console_type_text(console_type type);
  };
}
