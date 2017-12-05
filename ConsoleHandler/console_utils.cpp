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
    GetConsoleScreenBufferInfo(get_console_handler(), &buffer_info);
    return buffer_info.dwSize.X;
  }

  int console_utils::get_console_height()
  {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(get_console_handler(), &buffer_info);
    return buffer_info.srWindow.Bottom;
  }

  void console_utils::set_console_buffer_size(int height, int width)
  {
    PCONSOLE_SCREEN_BUFFER_INFOEX buffer_info;
    GetConsoleScreenBufferInfoEx(get_console_handler(), &buffer_info);
    buffer_info.dwSize.Y = height;
    buffer_info.dwSize.X = width;
    SetConsoleScreenBufferInfoEx(get_console_handler(), buffer_info);
  }

  _COORD console_utils::get_console_cursor_position()
  {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(get_console_handler(), &buffer_info);
    return buffer_info.dwCursorPosition;
  }

  void console_utils::set_console_cursor_pos(const _COORD cursor_position)
  {
    SetConsoleCursorPosition(get_console_handler(), cursor_position);
  }
}
