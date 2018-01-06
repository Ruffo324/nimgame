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
    static void draw_statistics();
  };
}

