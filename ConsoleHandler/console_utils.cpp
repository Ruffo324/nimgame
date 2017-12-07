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
    return buffer_info.dwSize.Y;
  }

  void console_utils::set_console_buffer_size(const int height, const int width)
  {
    const _COORD new_size = {short(width), short(height)};
    SetConsoleScreenBufferSize(get_console_handler(), new_size);
  }

  void console_utils::set_console_buffer_to_window_size()
  {
    //TODO: fix this shit
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    GetConsoleScreenBufferInfo(get_console_handler(), &console_screen_buffer_info);

    const _COORD new_size = { console_screen_buffer_info.dwMaximumWindowSize.X, console_screen_buffer_info.dwMaximumWindowSize.Y };
    SetConsoleScreenBufferSize(get_console_handler(), new_size);
  }

  /**
   * \brief Sets the console to the "Consolas" (or Lucida Console if Consolas not given)
   * font with the given font size
   * \param height The font height
   * \param width The font width
   */
  void console_utils::set_console_raster_font(const int height, const int width)
  {
    CONSOLE_FONT_INFOEX console_font_infoex;
    console_font_infoex.cbSize = sizeof console_font_infoex;
    console_font_infoex.nFont = 0;
    console_font_infoex.dwFontSize.X = width;
    console_font_infoex.dwFontSize.Y = height;
    console_font_infoex.FontFamily = FF_DONTCARE;
    console_font_infoex.FontWeight = FW_NORMAL;

    // apply font to the console with fallback to alternative font
    wcscpy_s(console_font_infoex.FaceName, L"Consolas");
    if(!SetCurrentConsoleFontEx(get_console_handler(), false, &console_font_infoex))
    {
      // change font to lucida console
      wcscpy_s(console_font_infoex.FaceName, L"Lucida Console");
      SetCurrentConsoleFontEx(get_console_handler(), false, &console_font_infoex);
    }
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

  void console_utils::set_console_window_size(const int height, const int width)
  {
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    GetConsoleScreenBufferInfo(get_console_handler(), &console_screen_buffer_info);

    console_screen_buffer_info.srWindow.Bottom = height;
    console_screen_buffer_info.srWindow.Right = width;
    SetConsoleWindowInfo(get_console_handler(), false, &console_screen_buffer_info.srWindow);
  }
}
