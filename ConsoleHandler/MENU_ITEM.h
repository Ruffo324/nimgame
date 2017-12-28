#pragma once
#include <string>

namespace console_handler
{
  //TODO: add constructor
  struct MENU_ITEM
  {
    std::string caption;
    std::string caption_foreground_color_code;

    std::string item_background;

    std::string icon_file;
    std::string icon_foreground_color_code;

    char border_char;
    std::string border_color_code;
    int border_size;

    int length;
    int width;

    MENU_ITEM(const std::string caption_value, const std::string caption_foreground_color_code_value,
              const std::string item_background_value, const std::string icon_file_value,
              const std::string icon_foreground_color_code_value, const char border_char_value,
              const std::string border_color_code_value, const int border_size_value)
      : caption(caption_value), caption_foreground_color_code(caption_foreground_color_code_value),
        item_background(item_background_value), icon_file(icon_file_value),
        icon_foreground_color_code(icon_foreground_color_code_value), border_char(border_char_value),
        border_color_code(border_color_code_value), border_size(border_size_value)
    {
    }
  };
}
