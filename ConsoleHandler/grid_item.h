#pragma once
#include <string>
#include "console_handler.h"

namespace console_handler
{
  class grid_item
  {
  public:
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

    CONSOLE_HANDLER_API grid_item(const std::string caption_value, const std::string caption_foreground_color_code_value,
              const std::string item_background_value, const std::string icon_file_value,
              const std::string icon_foreground_color_code_value, const char border_char_value,
              const std::string border_color_code_value, const int border_size_value);
  };
}
