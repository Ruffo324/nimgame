#pragma once
#include "console_handler.h"
#include <vector>
#include "menu_item.h"
#include "menu_item_rectangle.h"

namespace console_handler
{
  class dynamic_menu
  {
  public:
    void CONSOLE_HANDLER_API draw();
    void CONSOLE_HANDLER_API select();

    // Constructors
    CONSOLE_HANDLER_API dynamic_menu(std::vector<menu_item> menu_items, const int window_margin, const int margin_between_boxes);


  private:
    std::vector<menu_item_rectangle> items_;
    std::vector<menu_item> menu_items_;

    int item_side_length_;
    int boxes_per_row_;

    int rest_console_width_;
    int rest_console_height_;

    int window_margin_;
    int margin_between_boxes_;


    // caluclate functions
    int calculate_side_length_automatic() const;

    int calculate_boxes_per_row(int item_side_lenght) const;
    void calculate_rectangles();
  };
}
