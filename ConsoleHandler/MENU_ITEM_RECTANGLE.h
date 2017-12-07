#pragma once
#include <string>
#include "console_handler.h"
#include "MENU_ITEM.h"
#include "SHAPE_RECTANGLE.h"

namespace console_handler
{
  struct MENU_ITEM_RECTANGLE
  {
    /**
     * \brief THe original menu_item that was drawed
     */
    MENU_ITEM menu_item;

    /**
     * \brief The drawed rectangle for the menu item
     */
    SHAPE_RECTANGLE item_rectangle;

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
