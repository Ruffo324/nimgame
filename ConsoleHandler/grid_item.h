#pragma once
#include <string>
#include "console_handler.h"
#include <functional>

namespace console_handler
{
  class grid_item
  {
  public:
    std::string caption;
    std::string item_background;

    std::string icon_file;
    std::string icon_foreground_color_code;

    char border_char;
    std::string border_color_code;
    int border_size;


    int length;
    int width;
    void run() const;

    CONSOLE_HANDLER_API grid_item(std::function<void()> run_function_value, const std::string caption_value,
                                  const std::string item_background_value, const std::string icon_file_value,
                                  const std::string icon_foreground_color_code_value, const char border_char_value,
                                  const std::string border_color_code_value, const int border_size_value);
  private:
    std::function<void()> run_function;
  };
}
