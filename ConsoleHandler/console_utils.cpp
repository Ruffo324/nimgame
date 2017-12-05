#include "stdafx.h"
#include <Windows.h>
#include "console_utils.h"

namespace console_handler
{
  HANDLE console_utils::get_console_handler()
  {
    return GetStdHandle(STD_OUTPUT_HANDLE);
  }

  int console_utils::get_console_width()
  {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(console_utils::get_console_handler(), &buffer_info);
    return buffer_info.dwSize.X;
  }

  int console_utils::get_console_height()
  {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(console_utils::get_console_handler(), &buffer_info);
    return buffer_info.dwSize.Y;
  }

  /**
   * \brief Gets the correct text for the given console_type
   * \param console_type The console type wich is searched.
   * \return Text for the console_type
   */
  std::string console_utils::get_console_type_text(console_type type)
  {
    switch (type)
    {
    case info:
      return "INFO";
    case menu:
      return "MENU";
    default:
      return "????";
    }
  }
}
