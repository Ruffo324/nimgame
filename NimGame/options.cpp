#include "stdafx.h"
#include "options.h"
#include "console_output.h"
#include "ascii_block_list.h"
#include "console_utils.h"
#include "dynamic_grid.h"
#include "main.h"

namespace sites
{
  std::string options::name_player_a = "Player A";
  std::string options::name_player_b = "Player B";
  std::vector<int> options::field_structure = {1,2,3,4};
  int options::max_allowed_per_row = 3;
  int options::window_margin = 10;

  std::string options::site_background = "{_#FFFFFF}";
  std::string options::item_border_color = "{_#03b7a5}";
  std::string options::grid_caption_color = "{#43A047}";
  int options::grid_caption_font_size = 20;
  int options::border_size = 10;

  int options::max_cols = 10;
  int options::max_rows = 5;

  void options::draw()
  {
    console_handler::console_output::fill_background(site_background);

    std::vector<console_handler::grid_item> options_items;

    // Change names
    options_items.push_back(console_handler::grid_item([](bool selected)
                                                       {
                                                         change_player_names();
                                                         draw();
                                                       }, "{#FFFFFF}Change Names", "{_#66BB6A}",
                                                       "../Icons/Check.bmp", "{#FFFFFF}", ' ', item_border_color,
                                                       border_size));

    // Change Field Size
    options_items.push_back(console_handler::grid_item([](bool selected)
                                                       {
                                                         change_field_size_step_row();
                                                         draw();
                                                       }, "{#FFFFFF}Field", "{_#66BB6A}",
                                                       "../Icons/Resize.bmp", "{#FFFFFF}", ' ', item_border_color,
                                                       border_size));

    // Continue
    options_items.push_back(console_handler::grid_item([](bool selected) { main::draw(); }, "{#FFFFFF}Main menu",
                                                       "{_#757575}",
                                                       "../Icons/Cancle.bmp", "{#FFFFFF}", ' ', item_border_color,
                                                       border_size));

    // Draw question grid
    console_handler::dynamic_grid change_name_question =
      console_handler::dynamic_grid(grid_caption_color + "Options", grid_caption_font_size, options_items, 10, 5);
    change_name_question.set_size_multiplicator(0.5);
    change_name_question.recalculate_item_size();
    change_name_question.draw();
    change_name_question.select();
  }

  void options::change_field_size_step_row()
  {
    console_handler::console_output::fill_background(site_background);

    // Set amount of rows
    std::vector<console_handler::grid_item> select_row_count_items;
    for (int i = 1; i <= max_rows; i++)
    {
      select_row_count_items.push_back(console_handler::grid_item(
        [i](bool selected) mutable -> void { options::change_field_size_step_cols(i); }, "{#FFFFFF}" + std::to_string(i), "{_#43A047}", ' ',
        item_border_color, border_size / 2));
    }

    console_handler::dynamic_grid row_count_selection =
      console_handler::dynamic_grid(grid_caption_color + "Select number of rows:",
                                    grid_caption_font_size, select_row_count_items, window_margin, 5);
    row_count_selection.draw();
    row_count_selection.select();
  }

  void options::change_field_size_step_cols(const int rows)
  {
    // Clear pag
    console_handler::console_output::fill_background(site_background);

    // Calculate full possible grid field
    std::vector<int> new_field_structure;
    std::vector<console_handler::grid_item> full_grid_items;

    // each row
    for (int row = 0; row < rows; row++)
    {
      // max items
      for (int col = 1; col <= max_cols; col++)
      {
        full_grid_items.push_back(console_handler::grid_item([new_field_structure, col](bool selected) mutable -> void { },
          "{#FFFFFF}" + std::to_string(col), "{_#43A047}", ' ',
          item_border_color, 1));
      }
    }

    // Create & draw full grid
    console_handler::dynamic_grid grid_field_structure = console_handler::dynamic_grid(
      grid_caption_color + "Please adjust the field:", grid_caption_font_size, full_grid_items, window_margin, 5, max_cols);
    grid_field_structure.draw();

    int max_cols_copy = max_cols;

    // clear game field
    field_structure.clear();

    // select one from each row
    for (int row = 1; row <= rows; row++)
    {
      int amount = grid_field_structure.select(true, false, [row, max_cols_copy, &grid_field_structure]()
      {
        for (int i = row -1 + (max_cols_copy * row); i < row * max_cols_copy; i++)
        {
          grid_field_structure.disable_item(i, "{#424242}", "{#BDBDBD}");
        }
      }, true, max_cols_copy * (row -1)) % max_cols;
      field_structure.push_back(amount);
    }
    
    options::draw();
  }

  void options::change_player_names()
  {
    const int font_size = 20;
    console_handler::console_output::fill_background(site_background);
    console_handler::console_utils::set_console_cursor_pos({10, 10});
    _COORD console_cursor = console_handler::console_utils::get_console_cursor_position();

    // Player A
    console_handler::ascii_block_list text_a = console_handler::ascii_block_list("{#43A047}Name Player A", font_size);
    text_a.draw();
    console_handler::ascii_block_list name_a = console_handler::ascii_block_list(font_size);
    name_a.input(site_background);
    name_player_a = name_a.original_string;

    // Player B
    console_handler::console_utils::set_console_cursor_pos({console_cursor.X, console_cursor.Y + font_size * 2});
    console_handler::ascii_block_list text_b = console_handler::ascii_block_list("{#43A047}Name Player B", font_size);
    text_b.draw();
    console_handler::ascii_block_list name_b = console_handler::ascii_block_list(font_size);
    name_b.input(site_background);
    name_player_b = name_b.original_string;
  }
}
