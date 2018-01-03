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

    // Check for default players
    if (options::name_player_a == "Player A" || options::name_player_b == "Player B")
    {
      std::vector<console_handler::grid_item> change_name_items;

      // Change names
      change_name_items.push_back(console_handler::grid_item([](void) { options::change_player_names(); }, "{#FFFFFF}Change", "{_#8c9eff}",
        "../Icons/Check.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 5));

      // Continue
      change_name_items.push_back(console_handler::grid_item([](void) { play::draw(); }, "{#FFFFFF}Continue", "{_#8c9eff}",
        "../Icons/Cancle.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 5));

      console_handler::dynamic_grid change_name_question =
        console_handler::dynamic_grid("Default Playernames used. Statistic can't used.", 30, change_name_items, 10, 5);
      change_name_question.draw();
      change_name_question.select();

    }
  }

  void main::draw()
  {
    std::vector<console_handler::grid_item> menu_items;

    for(int i= 0;i < 2; i++) // debug
    { // debug
      
    // Play
    menu_items.push_back(console_handler::grid_item([](void) { start(); }, "{#FFFFFF}Play", "{_#8c9eff}",
      "../Icons/Play.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Options
    menu_items.push_back(console_handler::grid_item([](void) { options::draw(); }, "{#FFFFFF}Options", "{_#8c9eff}",
      "../Icons/Settings.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Stats
    menu_items.push_back(console_handler::grid_item([](void) { options::draw(); }, "{#FFFFFF}Statistics", "{_#8c9eff}",
      "../Icons/Stats.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    // Exit
    menu_items.push_back(console_handler::grid_item([](void) { /*TODO*/ }, "{#FFFFFF}Exit", "{_#8c9eff}",
      "../Icons/Exit.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 10));
    } // debug


    console_handler::dynamic_grid main_menu = console_handler::dynamic_grid("Nim Game!", 50, menu_items, 10, 5);
    main_menu.draw();
    main_menu.select();

  }
}
