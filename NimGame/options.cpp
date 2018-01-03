#include "stdafx.h"
#include "options.h"
#include "console_output.h"
#include "ascii_block_list.h"
#include "console_utils.h"

namespace sites
{
  std::string options::name_player_a = "Player A";
  std::string options::name_player_b = "Player B";

  void options::draw()
  {
  }

  void options::change_player_names()
  {
    console_handler::console_output::fill_background("{_#FFFFFF}");
    console_handler::console_utils::set_console_cursor_pos({10, 10});
    // Player A
    console_handler::ascii_block_list text_a = console_handler::ascii_block_list("Name Player A", 20);
    text_a.draw();
    console_handler::ascii_block_list name_a = console_handler::ascii_block_list(20);
    name_player_a = name_a.original_string;
    // Player B
    console_handler::ascii_block_list text_b = console_handler::ascii_block_list("Name Player B", 20);
    text_b.draw();
    console_handler::ascii_block_list name_b = console_handler::ascii_block_list(20);
    name_player_a = name_b.original_string;
  }
}
