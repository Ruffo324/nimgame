#pragma once
#include "console_handler.h"
#include <string>
#include "SHAPE_RECTANGLE.h"
#include "MENU_ITEM.h"
#include <vector>

namespace console_handler
{
  class CONSOLE_HANDLER_API console_output
  {
  public:
    static void print(std::string message);
    static void reset_color();
    static void print_line(std::string message);
    static void print_separatorline(std::string pattern);
    static void print_rectangle(SHAPE_RECTANGLE square, std::string color_string,
                                                    char text_char = ' ');
    // shapes
    static void fill_background(std::string color_string, char text_char = ' ');

    // menu
    static int draw_menu(std::vector<MENU_ITEM> menu_items, int window_margin, int margin_between_boxes, int boxes_per_row, bool recalculate_per_row = false);
  };
}
