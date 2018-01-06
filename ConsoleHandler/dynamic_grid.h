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
    /**
     * \brief Draws the dynamic grid complete
     */
    void CONSOLE_HANDLER_API draw();

    /**
     * \brief Set the dynamic_grid in the select mode.
     * \brief In this(default) mode, the action of the selected item, would run on {ENTER}
     */
    int CONSOLE_HANDLER_API select();

    /**
     * \brief Gets the full width and height of the drawed dynamic grid
     * \return The full size of the dynamic grid
     */
    SIZE CONSOLE_HANDLER_API get_full_size() const;

    /**
     * \brief Sets the grid in the select mode
     * \param run_item_action Should the item action run on {ENTER}
     * \param space_forces_return Can {SPACE} also used for selection? Would not run the item_action
     * \param optional_enter_action Optional action wich run on enter, default: nullptr
     * \param row_lock Should the selection locked by the current row? See: start_index parameter
     * \param start_index Where should the selection start?
     * \return index of the selected item
     */
    int CONSOLE_HANDLER_API select(const bool run_item_action, const bool space_forces_return,
      std::function<void()> optional_enter_action = nullptr, const bool row_lock = false, const int start_index = -1);

    /**
     * \brief Sets the grid in the mark & select mode.
     * \param row_lock is the select mode row locked? (Selected one item, other items only in the same row)
     * \param max_items How much items can be selected max? -1 for endless
     * \param select_color The color code for the selected items
     * \param selected_color_icon The icon color code for the selected items
     * \return list of the selected item indexes
     */
    std::vector<int> CONSOLE_HANDLER_API mark_and_select(const bool row_lock = false, const int max_items = -1, const std::string select_color = "{_#B0BEC5}", const std::string selected_color_icon = "{_#CFD8DC}");

    /**
     * \brief Sets the item size multiplicator
     * \param multiplicator Default: 1, Multiplicator for the item size. HINT: Values over 1 can result grapic bugs
     */
    void CONSOLE_HANDLER_API set_size_multiplicator(double multiplicator);

    /**
     * \brief Recalculates the size of the items to fit in the window
     */
    void CONSOLE_HANDLER_API recalculate_item_size();

    /**
     * \brief Disables an item by the given item index
     * \param index The index of the item wich should be disabled
     * \param disabled_background_color The background color of the disabled item
     * \param disabled_icon_color The Icon color of the disabled item
     */
    void CONSOLE_HANDLER_API disable_item(int index, std::string disabled_background_color, std::string disabled_icon_color);

    // Constructors
    // TODO: Doc comments
    CONSOLE_HANDLER_API dynamic_grid(std::vector<grid_item> menu_items, const int window_margin,
      const int margin_between_boxes);

    // TODO: Write dynamic_grid(caption, menu_items..) (automatic caption font_size calculation)
    CONSOLE_HANDLER_API dynamic_grid(const std::string grid_caption, const int caption_font_size,
      std::vector<grid_item> menu_items, const int window_margin,
      const int margin_between_boxes);

    CONSOLE_HANDLER_API dynamic_grid(const std::string grid_caption, const int caption_font_size,
      std::vector<grid_item> menu_items, const int window_margin,
      const int margin_between_boxes, const int boxes_per_row);

    /**
     * \brief Just an empty constructor
     */
    CONSOLE_HANDLER_API dynamic_grid();

    /**
     * \brief Checks if all items are disabled
     * \return true if alle items are disabled, false if not
     */
    bool CONSOLE_HANDLER_API all_items_disabled();

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
    void draw_item(grid_item_rectangle item) const;

  };
}
