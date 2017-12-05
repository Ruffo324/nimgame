#pragma once
#include "ConsoleHandler.h";
#include <Windows.h>;
#include <string>
#include "ConsoleTypes.h"

//#include "Cons"

namespace console_handler
{
  class console_utils
  {
  public:
    // Console base functions
    static CONSOLE_HANDLER_API HANDLE get_console_handler();
    static CONSOLE_HANDLER_API int get_console_width();
    static CONSOLE_HANDLER_API int get_console_height();
    static std::string get_console_type_text(console_types console_type);
  private:
    //static HWND current_console_handler_;
    console_utils();
    ~console_utils();
  };
}
