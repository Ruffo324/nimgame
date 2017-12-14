#include "stdafx.h"
#include "console_select.h"
#include <Windows.h>
#include <conio.h>
#include "console_output.h"
#include "console_utils.h"


namespace console_handler
{
  class console_utils;

  MENU_ITEM_RECTANGLE console_select::select_menu_item(std::vector<MENU_ITEM_RECTANGLE> menu_items)
  {
    int current_selected_index = 0;
    int last_selected_index = 0;
    CHAR input = 0;
    bool was_arrow_key = false;







    // until enter
    while (input != '\r')
    {
      if (last_selected_index != current_selected_index) {
        // Draw selection

        // redraw last
        console_output::print_rectangle(menu_items[last_selected_index].item_rectangle, menu_items[last_selected_index].menu_item.item_background);

        MENU_ITEM_RECTANGLE current_item = menu_items[current_selected_index];
        int item_height = current_item.item_rectangle.right.Y - current_item.item_rectangle.left.Y;
        int item_width = current_item.item_rectangle.right.X - current_item.item_rectangle.left.X;
        for (int i = 0; i < item_height; i++)
        {
          _COORD cursor_pos =
          { short(current_item.item_rectangle.left.X), short(current_item.item_rectangle.left.Y + short(i)) };
          console_utils::set_console_cursor_pos(cursor_pos);

          std::string line = "";
          for (int b = 0; b < item_width; b++)
          {
            // draw top & bottom
            if (i == 0 || i == item_height)
              line += "#";
            else
              if (b == 0 || b == item_width)
                line += "#";
              else
                line += " ";
          }
          console_output::print(line);

        }
      }

      // remind last index
      last_selected_index = current_selected_index;


      input = _getch();
      if (input == -32)
      {
        was_arrow_key = true;
        continue;
      }

      if (was_arrow_key)
        switch (input)
        {
          //  arrow rigth
        case 'M':
          current_selected_index++;
          if (current_selected_index + 1 > int(menu_items.size()))
            current_selected_index = 0;
          break;
          //  arrow left
        case 'K':
          current_selected_index--;
          if (current_selected_index < 0)
            current_selected_index = int(menu_items.size()) - 1;
          break;
          //  arrow up
        case 'H':
          break;
          //  arrow down
        case 'P':
          break;
        }

      was_arrow_key = false;
    }
    return menu_items[0];
  }
}
