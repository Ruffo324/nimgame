#include "stdafx.h"
#include "grid_item.h"

namespace console_handler
{
  void grid_item::run() const
  {
    run_function(selected);
  }

  grid_item::grid_item(const std::function<void(bool selected)> run_function_value, const std::string caption_value,
                       const std::string item_background_value, const std::string icon_file_value,
                       const std::string icon_foreground_color_code_value, const char border_char_value,
                       const std::string border_color_code_value, const int border_size_value)
    : caption(caption_value),
      item_background(item_background_value), icon_file(icon_file_value),
      icon_foreground_color_code(icon_foreground_color_code_value), border_char(border_char_value),
      border_color_code(border_color_code_value), border_size(border_size_value), run_function(run_function_value)
  {
  }

  grid_item::grid_item(const std::function<void(bool selected)> run_function_value, const std::string caption_value,
                       const std::string item_background_value, const char border_char_value,
                       const std::string border_color_code_value,
                       const int border_size_value)
    : caption(caption_value),
      item_background(item_background_value), icon_file(""),
      icon_foreground_color_code(""), border_char(border_char_value),
      border_color_code(border_color_code_value), border_size(border_size_value), run_function(run_function_value)
  {
  }
}
