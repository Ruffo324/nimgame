#pragma once
#include "console_handler.h"
#include <Windows.h>
#include <string>

namespace console_handler
{
  class console_utils
  {
  public:
    // get functions
    static CONSOLE_HANDLER_API HANDLE get_console_handle();
    static CONSOLE_HANDLER_API int get_console_width();
    static CONSOLE_HANDLER_API int get_console_height();
    static CONSOLE_HANDLER_API _COORD get_console_cursor_position();

    // set functions
    static CONSOLE_HANDLER_API void set_console_cursor_pos(_COORD cursor_position);
    static CONSOLE_HANDLER_API void set_console_window_size(int height, int width);
    static CONSOLE_HANDLER_API void set_console_buffer_size(int height, int width);
    static CONSOLE_HANDLER_API void set_console_buffer_to_window_size();

    static CONSOLE_HANDLER_API void set_console_raster_font(int height, int width);

    static CONSOLE_HANDLER_API void set_console_fullscreen();
    static CONSOLE_HANDLER_API void set_console_position(int top, int left);
    static CONSOLE_HANDLER_API void set_console_size(const int width, const int height, bool also_buffer = true);
    static CONSOLE_HANDLER_API void set_console_size_fixed();    
  };
}
