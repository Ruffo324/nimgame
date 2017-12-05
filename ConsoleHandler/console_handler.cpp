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
     
  }
};
