#include "stdafx.h"
#include "grid_item_rectangle.h"

namespace console_handler
{
  grid_item_rectangle::grid_item_rectangle(const console_handler::grid_item& menu_item,
                                           const shape_rectangle& item_rectangle, const int menu_row,
                                           const int menu_row_index)
    : grid_item(menu_item), item_rectangle(item_rectangle),
      grid_row(menu_row), grid_row_index(menu_row_index)
  {
  }
}
