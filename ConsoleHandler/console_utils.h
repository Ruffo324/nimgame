#pragma once
#include "console_handler.h"
#include <Windows.h>

namespace console_handler
{
  class CONSOLE_HANDLER_API console_utils
  {
  public:
    static int current_console_font_height;
    static int current_console_font_width;
    static bool fullscreen;
    // get functions
    static HANDLE get_console_handle();
    static int get_console_width();
    static int get_console_height();
    static _COORD get_console_cursor_position();

    // set functions
    static void set_console_cursor_pos(_COORD cursor_position);
    static void append_console_cursor_pos(_COORD cursor_position);
    static void set_console_buffer_size(int height, int width);
    static void set_console_buffer_to_window_size();

    static void set_console_raster_font(int size);

    static void set_console_fullscreen();
    static void set_console_position(int top, int left);
    static void set_console_size(const int width, const int height, bool also_buffer = true);
    static void set_console_size_fixed();    
  };
}
