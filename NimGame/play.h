#pragma once
#include "dynamic_grid.h"

namespace sites {
  class play
  {
  public:
    static void gameplay();
    static void new_game();
  private:
    static console_handler::dynamic_grid current_session_field_;
    static void generate_field();

    // statistics
    static void draw_statistics();
    static _COORD current_player_cursor_pos_;
    static _COORD selected_cursor_pos_;
    static _COORD picked_cursor_pos_;
    static _COORD remaining_cursor_pos_;
    static int font_size_;
  };
}

