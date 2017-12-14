#pragma once
#include <string>
#include "console_handler.h"

namespace console_handler
{
  struct MENU_ITEM
  {
    std::string caption;
    std::string item_background;
    std::string ascii_icon;
    char border_char;
    std::string border_color_code;
    int border_size;

    int length;
    int width;
  };
}
