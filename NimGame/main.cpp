#include "stdafx.h"
#include "main.h"
#include <vector>
#include "grid_item.h"
#include "options.h"
#include "dynamic_grid.h"
#include "console_output.h"
#include "ascii_block_list.h"
#include "play.h"


namespace sites
{
  void main::start()
  {
    console_handler::console_output::fill_background("{_#FFFFFF}");

    // Check for default player names
    if (options::name_player_a == "Player A" || options::name_player_b == "Player B")
    {
      std::vector<console_handler::grid_item> change_name_items;

      // Change names
      change_name_items.push_back(console_handler::grid_item([](bool selected) { options::change_player_names(); play::new_game(); }, "{#FFFFFF}Change", "{_#66BB6A}",
        "../Icons/Check.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));

      // Continue
      change_name_items.push_back(console_handler::grid_item([](bool selected) { play::new_game(); }, "{#FFFFFF}Continue", "{_#388E3C}",
        "../Icons/Cancle.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));

      // Draw question grid
      console_handler::dynamic_grid change_name_question =
        console_handler::dynamic_grid("{#43A047}Default Playernames, statistic can't used.", 20, change_name_items, 10, 5);
      change_name_question.set_size_multiplicator(0.5);
      change_name_question.recalculate_item_size();
      change_name_question.draw();
      change_name_question.select();
    }
  }

  void main::draw()
  {
    const int item_font_size = 20;
    console_handler::console_output::fill_background("{_#FFFFFF}");

    std::vector<console_handler::grid_item> menu_items;
      
    // Play
    menu_items.push_back(console_handler::grid_item([](bool selected) { start(); }, "{#FFFFFF}Play", "{_#66BB6A}",
      "../Icons/Play.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Options
    menu_items.push_back(console_handler::grid_item([](bool selected) { options::draw(); }, "{#FFFFFF}Options", "{_#43A047}",
      "../Icons/Settings.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Stats
    menu_items.push_back(console_handler::grid_item([](bool selected) { options::draw(); }, "{#FFFFFF}Statistics", "{_#388E3C}",
      "../Icons/Stats.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Exit
    menu_items.push_back(console_handler::grid_item([](bool selected) { /*TODO*/ }, "{#FFFFFF}Exit", "{_#2E7D32}",
      "../Icons/Exit.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));

    console_handler::dynamic_grid main_menu = console_handler::dynamic_grid("{#43A047}Nim Game!", 30, menu_items, 10, 5, 2);
    main_menu.draw();
    main_menu.select();

  }
}
