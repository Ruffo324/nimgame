#include "stdafx.h"
#include <Windows.h>
#include "console_utils.h"

namespace console_handler
{
  HANDLE console_utils::get_console_handle()
  {
    return GetStdHandle(STD_OUTPUT_HANDLE);
  }

  int console_utils::get_console_width()
  {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(get_console_handle(), &buffer_info);
    return buffer_info.dwSize.X;
  }

  int console_utils::get_console_height()
  {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(get_console_handle(), &buffer_info);
    return buffer_info.dwSize.Y;
  }

  void console_utils::set_console_buffer_size(const int height, const int width)
  {
    const _COORD new_size = {short(width), short(height)};
    SetConsoleScreenBufferSize(get_console_handle(), new_size);
  }

  void console_utils::set_console_buffer_to_window_size()
  {
    RECT r;
    GetWindowRect(GetConsoleWindow(), &r);
    set_console_buffer_size(abs(r.bottom-r.top), abs(r.right-r.left));
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
    font_size_height = height;
    font_size_width = width;
    console_font_infoex.FontFamily = FF_DONTCARE;
    console_font_infoex.FontWeight = FW_NORMAL;

    // apply font to the console with fallback to alternative font
    wcscpy_s(console_font_infoex.FaceName, L"Consolas");
    if (!SetCurrentConsoleFontEx(get_console_handle(), false, &console_font_infoex))
    {
      // change font to lucida console
      wcscpy_s(console_font_infoex.FaceName, L"Lucida Console");
      SetCurrentConsoleFontEx(get_console_handle(), false, &console_font_infoex);
    }
  }

  void console_utils::set_console_fullscreen()
  {
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
  }

  void console_utils::set_console_position(const int top, const int left)
  {
    RECT r;
    GetWindowRect(GetConsoleWindow(), &r);
    MoveWindow(GetConsoleWindow(), left, top, r.right, r.bottom, TRUE);
  }

  void console_utils::set_console_size_fixed()
  {
    const HMENU hmenu = GetSystemMenu(GetConsoleWindow(), false);
    DeleteMenu(hmenu, SC_MINIMIZE, MF_BYCOMMAND);
    DeleteMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);
    DeleteMenu(hmenu, SC_SIZE, MF_BYCOMMAND);
  }

  void console_utils::set_console_size(const int width, const int height, const bool also_buffer)
  {
    RECT r;
    GetWindowRect(GetConsoleWindow(), &r);
    MoveWindow(GetConsoleWindow(), r.left, r.top, width, height, TRUE);

    if (also_buffer)
      set_console_buffer_to_window_size();
  }

  _COORD console_utils::get_console_cursor_position()
  {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(get_console_handle(), &buffer_info);
    return buffer_info.dwCursorPosition;
  }

  void console_utils::set_console_cursor_pos(const _COORD cursor_position)
  {
    SetConsoleCursorPosition(get_console_handle(), cursor_position);
  }

  void console_utils::set_console_window_size(const int height, const int width)
  {
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
    GetConsoleScreenBufferInfo(get_console_handle(), &console_screen_buffer_info);

    console_screen_buffer_info.srWindow.Bottom = height;
    console_screen_buffer_info.srWindow.Right = width;
    SetConsoleWindowInfo(get_console_handle(), false, &console_screen_buffer_info.srWindow);
  }
}
