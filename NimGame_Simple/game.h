#pragma once
#include <vector>

class game
{
public:
  static void new_game_init();
private:
  static bool player_a_is;
  static std::vector<int> current_game;

  static void draw_field(int empty_lines);
  static void win_screen();
  static void gameplay();
  static int player_input(std::string prefix);
};
