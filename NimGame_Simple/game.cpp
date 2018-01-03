#include "stdafx.h"
#include "game.h"
#include "settings.h"
#include "console_output.h"
#include "console_utils.h"
#include <iostream>
#include "main_menu.h"


std::vector<int> game::current_game;
bool game::player_a_is = false;

void game::new_game_init()
{
  console_handler::console_output::fill_background("{#FFFDE7}");

  // reset field
  current_game = settings::rows;
  player_a_is = false;

  gameplay();


}

void game::draw_field(int empty_lines)
{
  console_handler::console_utils::set_console_cursor_pos({ 0,0 });
  console_handler::console_output::clear_screen();

  console_handler::console_output::print_separatorline("{#C5E1A5}=");
  console_handler::console_utils::set_console_cursor_pos({ 0,1 });
  // draw new gamefield
  for (int i = 0; i < current_game.size(); i++)
  {
    console_handler::console_output::print("{#EEEEEE1}" + std::to_string(i) + " | ");

    for (int a = 0; a < current_game[i]; a++)
    {
      console_handler::console_output::print(" {#FFB300}i ");
    }
    console_handler::console_output::print("\n");
  }

  for (int i = 0; i < empty_lines; i++)
    console_handler::console_output::print_separatorline("{#FFFFFF} ");

  console_handler::console_output::print_separatorline("{#C5E1A5}=");
}

void game::win_screen()
{
  console_handler::console_output::clear_screen();
  
  console_handler::console_utils::set_console_cursor_pos({ 0,0 });
  console_handler::console_output::print_separatorline("{#C5E1A5}=");
  console_handler::console_output::print_line("{#E0E0E0}Winner: {#84FFFF}" + std::string((player_a_is ? settings::player_name_a : settings::player_name_b)));

  // And again
  console_handler::console_output::print_separatorline("{#C5E1A5}=");
  console_handler::console_output::print_line("\t{#757575}1\t{#82B1FF}Again");
  console_handler::console_output::print_line("\t{#757575}2\t{#82B1FF}Main Menu");
  console_handler::console_output::print_separatorline("{#C5E1A5}=");
  int next = -1;
  while (next < 1 || next > 2)
    next = player_input("");

  if (next == 1)
    new_game_init();
  else if (next == 2)
    main_menu::show_main_menu();
}

void game::gameplay()
{
  int empty_lines = 0;
  while (!current_game.empty())
  {
    player_a_is = !player_a_is;

    draw_field(empty_lines);
    const _COORD current_cursor_position = console_handler::console_utils::get_console_cursor_position();
    console_handler::console_output::print_line("{#84FFFF}" + std::string((player_a_is ? settings::player_name_a : settings::player_name_b)));
    int row = -1, count = -1;
    while (row < 0 || row >= current_game.size() || current_game[row] == 0)
    {
      // Clear console line
      console_handler::console_utils::set_console_cursor_pos({ current_cursor_position.X, current_cursor_position.Y + 1 });
      console_handler::console_output::print_separatorline("{#FFFFFF} ");
      console_handler::console_utils::set_console_cursor_pos({ current_cursor_position.X, current_cursor_position.Y + 1 });
      row = player_input("{#9CCC65}Row ");
    }
    while (count < 1 || count > settings::max_per_row_allowed || current_game[row] < count)
    {
      // Clear console line
      console_handler::console_utils::set_console_cursor_pos({ current_cursor_position.X, current_cursor_position.Y + 2 });
      console_handler::console_output::print_separatorline("{#FFFFFF} ");
      console_handler::console_utils::set_console_cursor_pos({ current_cursor_position.X, current_cursor_position.Y + 2 });
      count = player_input("{#9CCC65}Count ");
    }

    current_game[row] -= count;
    if (current_game[row] == 0)
    {
      empty_lines++;
      current_game.erase(current_game.begin() + row);
    }

    console_handler::console_utils::set_console_cursor_pos({ 0,current_cursor_position.Y });
    console_handler::console_output::print_separatorline("{#FFFFFF} ");
    console_handler::console_output::print_separatorline("{#FFFFFF} ");
    console_handler::console_output::print_separatorline("{#FFFFFF} ");
    console_handler::console_utils::set_console_cursor_pos({ current_cursor_position.X,current_cursor_position.Y });
  }

  win_screen();
}

int game::player_input(std::string prefix)
{
  const _COORD current_cursor_position = console_handler::console_utils::get_console_cursor_position();

  int value = -1;
  while (value < 0)
  {
    console_handler::console_utils::set_console_cursor_pos({ current_cursor_position.X,current_cursor_position.Y });

    console_handler::console_output::print(prefix);
    console_handler::console_output::print("{#82B1FF}> {#FF5252}");
    std::cin >> value;
    std::cin.clear();
    if (value < 0)
      std::cin.ignore();
  }
  return value;
}


