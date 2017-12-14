#pragma once
#include "console_handler.h"
#include "MENU_ITEM_RECTANGLE.h"
#include <vector>

namespace console_handler
{

  class CONSOLE_HANDLER_API console_select
  {
  public:
    static MENU_ITEM_RECTANGLE select_menu_item(std::vector<MENU_ITEM_RECTANGLE> menu_items);
  };
}

