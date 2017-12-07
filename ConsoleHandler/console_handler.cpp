#include "stdafx.h"
#include "console_handler.h"
#include <stdexcept>
#include <Windows.h>
#include "console_utils.h"

namespace console_handler
{
   void console_handler_core::prepare_console()
  {
     // set console mode for color support
     DWORD current_mode;
     GetConsoleMode(console_utils::get_console_handler(), &current_mode);
     current_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
     SetConsoleMode(console_utils::get_console_handler(), current_mode);

     // set console buffer size
     //TODO: console_buffer_size and window_size set
     //console_utils::set_console_buffer_size(5, 5);
     //console_utils::set_console_window_size(5, 5);
     console_utils::set_console_buffer_to_window_size();

     // set console font to sqaure like font
     console_utils::set_console_raster_font(5, 5);
     
  }
};
