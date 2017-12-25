#pragma once
#include "MENU_ITEM.h"
#include "SHAPE_RECTANGLE.h"

namespace console_handler
{
  struct MENU_ITEM_RECTANGLE
  {
    MENU_ITEM_RECTANGLE(const MENU_ITEM& menu_item, const SHAPE_RECTANGLE& item_rectangle,
                        const int menu_row, const int menu_row_index)
      : menu_item(menu_item),
        item_rectangle(item_rectangle),
        menu_row(menu_row),
        menu_row_index(menu_row_index)
    {
    }

    explicit MENU_ITEM_RECTANGLE(const MENU_ITEM& menu_item) : menu_item(menu_item)
    {
    }

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
