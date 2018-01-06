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
      change_name_items.push_back(console_handler::grid_item([](bool selected) { options::change_player_names(); play::new_game(); }, "{#FFFFFF}Change", "{_#8c9eff}",
        "../Icons/Check.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));

      // Continue
      change_name_items.push_back(console_handler::grid_item([](bool selected) { play::new_game(); }, "{#FFFFFF}Continue", "{_#8c9eff}",
        "../Icons/Cancle.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));

      // Draw question grid
      console_handler::dynamic_grid change_name_question =
        console_handler::dynamic_grid("Default Playernames, statistic can't used.", 20, change_name_items, 10, 5);
      change_name_question.set_size_multiplicator(0.5);
      change_name_question.recalculate_item_size();
      change_name_question.draw();
      change_name_question.select();
    }
  }

  void main::draw()
  {
    console_handler::console_output::fill_background("{_#FFFFFF}");

    std::vector<console_handler::grid_item> menu_items;

   // for(int i= 0;i < 3; i++) // debug
    //{ // debug
      
    // Play
    menu_items.push_back(console_handler::grid_item([](bool selected) { start(); }, "{#FFFFFF}Play", "{_#8c9eff}",
      "../Icons/Play.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Options
    menu_items.push_back(console_handler::grid_item([](bool selected) { options::draw(); }, "{#FFFFFF}Options", "{_#8c9eff}",
      "../Icons/Settings.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Stats
    menu_items.push_back(console_handler::grid_item([](bool selected) { options::draw(); }, "{#FFFFFF}Statistics", "{_#8c9eff}",
      "../Icons/Stats.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Exit
    menu_items.push_back(console_handler::grid_item([](bool selected) { /*TODO*/ }, "{#FFFFFF}Exit", "{_#8c9eff}",
      "../Icons/Exit.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    //} // debug


    console_handler::dynamic_grid main_menu = console_handler::dynamic_grid("Nim Game!", 50, menu_items, 10, 5);
    main_menu.draw();
    main_menu.select();

  }
}
