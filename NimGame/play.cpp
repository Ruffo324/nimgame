#include "stdafx.h"
#include "play.h"
#include "console_output.h"
#include "options.h"

namespace sites
{
  console_handler::dynamic_grid play::current_session_field_;

  void play::gameplay()
  {

  }

  void play::new_game()
  {
    //TODO: Make pretty game-color design
    console_handler::console_output::fill_background("{_#FFFFFF}");
    generate_field();
    current_session_field_.draw();
    current_session_field_.select();
  }

  void play::generate_field()
  {
    std::vector<console_handler::grid_item> field_items;

    // Get max items per row given
    int max_items_per_row = 0;
    for (int row = 0; row < options::field_structure.size(); row++)
    {
      if (max_items_per_row < options::field_structure[row])
        max_items_per_row = options::field_structure[row];
    }

    for (int row = 0; row < options::field_structure.size(); row++)
    {
      for (int field_item = 1; field_item <= max_items_per_row; field_item++)
      {
        //(currently) testing center boxes (MAKE THIS LATER @ME(CG))
        // THE TIME IS RUNNING AWAY!

        //if(max_items_per_row != options::field_structure[row])
        //{
        //  if(max_items_per_row % options::field_structure[row] == 0)
        //  {
        //    if (field_item < max_items_per_row / options::field_structure[row] || field_i)
        //    
        //  }
        //  else
        //  {
        //  }
        //}

        bool disiabled_item = false;
        if (field_item > options::field_structure[row])
          disiabled_item = true;//true;

        console_handler::grid_item new_field_item = console_handler::grid_item([](void) {}, "", "{_#FDD835}", "../Icons/FireMatch.bmp", "{_#D84315}", ' ', "{_#37474F}", 5);
        new_field_item.disabled = disiabled_item;
        new_field_item.visible = !disiabled_item;
        field_items.push_back(new_field_item);
      }
    }
    current_session_field_ = console_handler::dynamic_grid("Go!", 30, field_items, 10, 5, max_items_per_row);
  }
}
