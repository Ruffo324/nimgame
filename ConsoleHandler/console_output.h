#pragma once
#include "console_handler.h"
#include <string>
#include "SHAPE_RECTANGLE.h"
#include "menu_item.h"
#include <vector>

namespace console_handler
{
  struct menu_item_rectangle;

  class CONSOLE_HANDLER_API console_output
  {
  public:
    static void print(std::string message);
    static void reset_color();
    static void print_line(std::string message);
    static void print_separatorline(std::string pattern);

    // shapes
    static void fill_background(std::string color_string, char text_char = ' ');

  private:
    static void internal_write(std::string message);
  };
}
