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
    static bool player_a_is_;

    // propertys
    static std::string background_color_;
    static std::string text_value_color_;
    static std::string caption_color_;

    // statistics
    static void draw_statistics();
    static void draw_current_player(const std::string current_player, const std::string last_player);
    static void draw_selected(const int selected, const int last_selected);
    static void draw_remaining(const int remaining, const int last_remaining);
    static void draw_picked(const int picked, const int last_picked);

    static _COORD current_player_cursor_pos_;
    static _COORD selected_cursor_pos_;
    static _COORD picked_cursor_pos_;
    static _COORD remaining_cursor_pos_;
    static int font_size_;


  };
}

