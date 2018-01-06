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
    /**
     * \brief Set the dynamic_grid in the select mode. 
     * \brief In this(default) mode, the action of the selected item, would run on {ENTER}
     */
    int CONSOLE_HANDLER_API select();
    int CONSOLE_HANDLER_API select(const bool run_item_action, const bool space_forces_return);
    std::vector<int> CONSOLE_HANDLER_API mark_and_select(const bool row_lock = false);

    void CONSOLE_HANDLER_API set_size_multiplicator(double multiplicator);
    void CONSOLE_HANDLER_API recalculate_item_size();

    // Constructors
    CONSOLE_HANDLER_API dynamic_grid(std::vector<grid_item> menu_items, const int window_margin,
                                     const int margin_between_boxes);
    // TODO: Write dynamic_grid(caption, menu_items..) (automatic caption font_size calculation)
    CONSOLE_HANDLER_API dynamic_grid(const std::string grid_caption, const int caption_font_size,
                                     std::vector<grid_item> menu_items, const int window_margin,
                                     const int margin_between_boxes);

    CONSOLE_HANDLER_API dynamic_grid(const std::string grid_caption, const int caption_font_size,
      std::vector<grid_item> menu_items, const int window_margin,
      const int margin_between_boxes, const int boxes_per_row);

    // Default empty constructor
    CONSOLE_HANDLER_API dynamic_grid();
  private:
    std::vector<grid_item_rectangle> items_;
    std::vector<grid_item> menu_items_;

    int item_side_length_;
    int boxes_per_row_;

    int window_margin_;
    int margin_between_boxes_;

    int longest_caption_length_ = 5;

    double size_multiplicator_ = 1;

    // Caption
    std::string caption_;
    int caption_font_size_;
    int caption_top_offset_;
    void draw_caption() const;

    // init
    void auto_sized_grid_init();

    // caluclate functions
    int calculate_side_length_automatic() const;
    int calculate_side_length(const int items_per_row) const;
    int calculate_boxes_per_row(int item_side_lenght) const;
    void calculate_rectangles();

  };
}
