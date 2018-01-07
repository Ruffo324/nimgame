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
  std::vector<int> options::field_structure = { 1,2,3,4 };
  int options::max_allowed_per_row = 3;
  int options::window_margin = 10;

  void options::draw()
  {
    const std::string site_background = "{_#FFFFFF}";
    console_handler::console_output::fill_background(site_background);

    std::vector<console_handler::grid_item> options_items;

    // Change names
    options_items.push_back(console_handler::grid_item([](bool selected) { options::change_player_names(); options::draw(); }, "{#FFFFFF}Change Names", "{_#66BB6A}",
      "../Icons/Check.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));

    // Continue
    options_items.push_back(console_handler::grid_item([](bool selected) {main::draw(); }, "{#FFFFFF}Main menu", "{_#388E3C}",
      "../Icons/Cancle.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));

    // Draw question grid
    console_handler::dynamic_grid change_name_question =
      console_handler::dynamic_grid("{#43A047}Options", 20, options_items, 10, 5);
    change_name_question.set_size_multiplicator(0.5);
    change_name_question.recalculate_item_size();
    change_name_question.draw();
    change_name_question.select();
  }

  void options::change_player_names()
  {
    const std::string site_background = "{_#FFFFFF}";
    const int font_size = 20;
    console_handler::console_output::fill_background(site_background);
    console_handler::console_utils::set_console_cursor_pos({ 10, 10 });
    _COORD console_cursor = console_handler::console_utils::get_console_cursor_position();
    // Player A
    console_handler::ascii_block_list text_a = console_handler::ascii_block_list("{#43A047}Name Player A", font_size);
    text_a.draw();
    console_handler::ascii_block_list name_a = console_handler::ascii_block_list(font_size);
    name_a.input(site_background);
    name_player_a = name_a.original_string;

    // Player B
    console_handler::console_utils::set_console_cursor_pos({ console_cursor.X, console_cursor.Y + font_size * 2 });
    console_handler::ascii_block_list text_b = console_handler::ascii_block_list("{#43A047}Name Player B", font_size);
    text_b.draw();
    console_handler::ascii_block_list name_b = console_handler::ascii_block_list(font_size);
    name_b.input(site_background);
    name_player_b = name_b.original_string;
  }
}
