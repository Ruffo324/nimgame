#include "stdafx.h"
#include <Windows.h>
#include "console_utils.h"

namespace console_handler
{
  int console_utils::current_console_font_height = 1;
  int console_utils::current_console_font_width = 1;
  bool console_utils::fullscreen = false;

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
    //TODO: 
    //https://msdn.microsoft.com/en-us/library/windows/desktop/ms724947(v=vs.85).aspx
    // Calculate buffer size with font-height.
    const _COORD new_size = {
      short(width / int(current_console_font_width)),
      short(height / int(current_console_font_height))
    };
    SetConsoleScreenBufferSize(get_console_handle(), new_size);
  }

  void console_utils::set_console_buffer_to_window_size()
  {

    _CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(get_console_handle(), &info);

    if (fullscreen)
    {
      RECT r;
      GetWindowRect(GetConsoleWindow(), &r);
     // set_console_buffer_size(((r.bottom - r.top) / 2) - 9, ((r.right - r.left) / 2) - 8);
      set_console_buffer_size(((r.bottom - r.top) - 1) / 2 , ((r.right - r.left) - 1) / 2);
    }
    else
    {
      RECT r;
      GetWindowRect(GetConsoleWindow(), &r);

      int old_height_buffer = info.dwSize.Y;
      int width = info.srWindow.Right - info.srWindow.Left + 1;
      int height = info.srWindow.Bottom - info.srWindow.Top;
      //TODO: Make this móre comfortable
      for (int i = 0; info.dwSize.Y == old_height_buffer; i++)
      {
        height++;
        set_console_buffer_size(height, width);
        GetConsoleScreenBufferInfo(get_console_handle(), &info);
      }
    }

  }

  /**
   * \brief Sets the console to the "Consolas" (or Lucida Console if Consolas not given)
   * \param size wanted font size
   */
  void console_utils::set_console_raster_font(const int size)
  {
    current_console_font_height = size;//(size * 2) -2;
    //if (current_console_font_height <= size) 
    //  current_console_font_height = size * 2;

    current_console_font_width = size;
    CONSOLE_FONT_INFOEX console_font_infoex;
    console_font_infoex.cbSize = sizeof console_font_infoex;
    console_font_infoex.nFont = 0;
    console_font_infoex.dwFontSize.X = current_console_font_width;
    console_font_infoex.dwFontSize.Y = current_console_font_height;
    console_font_infoex.FontFamily = FW_DONTCARE;
    console_font_infoex.FontWeight = FW_NORMAL;

    // apply font to the console with fallback to alternative font
    wcscpy_s(console_font_infoex.FaceName, L"Lucida Console");
    // wcscpy_s(console_font_infoex.FaceName, L"Terminal");
    if (!SetCurrentConsoleFontEx(get_console_handle(), false, &console_font_infoex))
    {
      // change font to lucida console
      wcscpy_s(console_font_infoex.FaceName, L"Consolas");
      SetCurrentConsoleFontEx(get_console_handle(), false, &console_font_infoex);
    }
  }

  void console_utils::set_console_fullscreen()
  {
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    fullscreen = true;
    set_console_buffer_to_window_size();
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
    ////MoveWindow(GetConsoleWindow(), 0, 0, width, height, TRUE);
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
}
