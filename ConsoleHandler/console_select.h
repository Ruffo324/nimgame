#pragma once
#include "console_handler.h"
#include "grid_item_rectangle.h"
#include <vector>

namespace console_handler
{

  class CONSOLE_HANDLER_API console_select
  {
  public:
    static grid_item_rectangle select_menu_item(std::vector<grid_item_rectangle> menu_items);
  private:
    static void draw_border_around_menu_item(const grid_item_rectangle menu_item, char border_char, std::string border_color_code);

  };
}

