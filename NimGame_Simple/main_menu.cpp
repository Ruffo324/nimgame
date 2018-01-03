#include "stdafx.h"
#include "main_menu.h"
#include "console_output.h"
#include "console_utils.h"
#include <iostream>
#include "game.h"

void main_menu::show_main_menu()
{

  console_handler::console_output::clear_screen();
  console_handler::console_utils::set_console_cursor_pos({0, 0});
  console_handler::console_output::print_line("\t{#FFAB91}Main Menu");
  console_handler::console_output::print_line("\t{#757575}1\t{#82B1FF}Play");
  console_handler::console_output::print_line("\t{#757575}2\t{#82B1FF}Settings");
  console_handler::console_output::print_line("\t{#757575}3\t{#82B1FF}Exit");

  // select user input
  int selected_item;
  do
  {
    selected_item = select();
  }
  while (selected_item < 1 || selected_item > 3);

  switch(selected_item)
  {
  case 1:
    game::new_game_init();
    break;
  case 2:
    console_handler::console_output::print("Not implemented currently.");
    show_main_menu();
    break;
  default: 
    break;
    ;
  }
}

int main_menu::select()
{
  int value = -1;
  while (value < 0)
  {
    console_handler::console_output::print("{#82B1FF}> {#FF5252}");
    std::cin >> value;
    std::cin.clear();
    if (value < 0)
      std::cin.ignore();
  }
  return value;
}
