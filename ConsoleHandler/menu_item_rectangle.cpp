#include "stdafx.h"
#include "menu_item_rectangle.h"

namespace console_handler
{
  menu_item_rectangle::menu_item_rectangle(const console_handler::menu_item& menu_item,
                                           const shape_rectangle& item_rectangle, const int menu_row,
                                           const int menu_row_index)
    : menu_item(menu_item), item_rectangle(item_rectangle),
      menu_row(menu_row), menu_row_index(menu_row_index)
  {
  }
}
