#pragma once
#include "console_handler.h"
#include <Windows.h>
#include <string>

namespace console_handler
{
  class console_utils
  {
  public:
    // Console base functions
    // get functions
    static CONSOLE_HANDLER_API HANDLE get_console_handler();
    static CONSOLE_HANDLER_API int get_console_width();
    static CONSOLE_HANDLER_API int get_console_height();
    static void set_console_buffer_size(int height, int width);
    static CONSOLE_HANDLER_API _COORD get_console_cursor_position();

    // set functions
    static CONSOLE_HANDLER_API void set_console_cursor_pos(_COORD cursor_position);
  };
}
