#include "stdafx.h"
#include <Windows.h>
#include "ConsoleUtils.h"

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
  std::string console_utils::get_console_type_text(const console_types console_type)
  {
    switch (console_type)
    {
    info:
      return "INFO";
    menu:
      return "MENU";
    default:
      return "????";
    }
  }

  console_utils::console_utils()
  {
  }


  console_utils::~console_utils()
  {
  }
}
