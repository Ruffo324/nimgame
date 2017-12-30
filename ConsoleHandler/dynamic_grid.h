#pragma once
#include "console_handler.h"
#include <vector>
#include "grid_item.h"
#include "grid_item_rectangle.h"

namespace console_handler
{
  class dynamic_grid
  {
  public:
    void CONSOLE_HANDLER_API draw();
    grid_item_rectangle CONSOLE_HANDLER_API select();

    // Constructors
    CONSOLE_HANDLER_API dynamic_grid(std::vector<grid_item> menu_items, const int window_margin,
                                     const int margin_between_boxes);
    // TODO: Write dynamic_grid(caption, menu_items..) (automatic caption font_size calculation)
    CONSOLE_HANDLER_API dynamic_grid(const std::string grid_caption, const int caption_font_size,
                                     std::vector<grid_item> menu_items, const int window_margin,
                                     const int margin_between_boxes);

  private:
    std::vector<grid_item_rectangle> items_;
    std::vector<grid_item> menu_items_;

    int item_side_length_;
    int boxes_per_row_;

    int window_margin_;
    int margin_between_boxes_;

    // Caption
    std::string caption_;
    int caption_font_size_;
    int caption_top_offset_;
    void draw_caption() const;

    // init
    void auto_sized_grid_init();

    // caluclate functions
    int calculate_side_length_automatic() const;
    int calculate_boxes_per_row(int item_side_lenght) const;
    void calculate_rectangles();
  };
}
