#include "stdafx.h"
#include "options.h"
#include "console_output.h"
#include "ascii_block_list.h"
#include "console_utils.h"

namespace sites
{
  std::string options::name_player_a = "Player A";
  std::string options::name_player_b = "Player B";
  std::vector<int> options::field_structure = { 1,2,3,4 };
  int options::max_allowed_per_row = 3;
  int options::window_margin = 10;

  void options::draw()
  {
  }

  void options::change_player_names()
  {
    const std::string site_background = "{_#FFFFFF}";
    const int font_size = 20;
    console_handler::console_output::fill_background(site_background);
    console_handler::console_utils::set_console_cursor_pos({ 10, 10 });
    _COORD console_cursor = console_handler::console_utils::get_console_cursor_position();
    // Player A
    console_handler::ascii_block_list text_a = console_handler::ascii_block_list("Name Player A", font_size);
    text_a.draw();
    console_handler::ascii_block_list name_a = console_handler::ascii_block_list(font_size);
    name_a.input(site_background);
    name_player_a = name_a.original_string;

    // Player B
    console_handler::console_utils::set_console_cursor_pos({ console_cursor.X, console_cursor.Y + font_size * 2 });
    console_handler::ascii_block_list text_b = console_handler::ascii_block_list("Name Player B", font_size);
    text_b.draw();
    console_handler::ascii_block_list name_b = console_handler::ascii_block_list(font_size);
    name_b.input(site_background);
    name_player_a = name_b.original_string;
  }
}
