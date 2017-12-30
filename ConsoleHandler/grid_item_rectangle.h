#pragma once
#include "grid_item.h"
#include "SHAPE_RECTANGLE.h"

namespace console_handler
{
  class grid_item_rectangle
  {
  public:
    grid_item_rectangle(const grid_item& grid_item, const shape_rectangle& item_rectangle,
                        const int menu_row, const int menu_row_index);

    /**
     * \brief THe original menu_item that was drawed
     */
    grid_item grid_item;

    /**
     * \brief The drawed rectangle for the menu item
     */
    shape_rectangle item_rectangle;

    /**
     * \brief The row where the item is drawd
     */
    int grid_row;

    /**
     * \brief The index of the item in the row
     */
    int grid_row_index;
  };
}
