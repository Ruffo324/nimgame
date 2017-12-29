#pragma once
#include "menu_item.h"
#include "SHAPE_RECTANGLE.h"

namespace console_handler
{
  class menu_item_rectangle
  {
  public:
    menu_item_rectangle(const menu_item& menu_item, const shape_rectangle& item_rectangle,
                        const int menu_row, const int menu_row_index);

    /**
     * \brief THe original menu_item that was drawed
     */
    menu_item menu_item;

    /**
     * \brief The drawed rectangle for the menu item
     */
    shape_rectangle item_rectangle;

    /**
     * \brief The row where the item is drawd
     */
    int menu_row;

    /**
     * \brief The index of the item in the row
     */
    int menu_row_index;
  };
}
