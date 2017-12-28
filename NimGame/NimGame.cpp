// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_handler.h"
#include <iostream>
#include "console_output.h"
#include "console_utils.h"
#include "console_select.h"
#include "console_ascii.h"

using namespace std;
using namespace console_handler;

int main()
{
  console_handler_core::prepare_console(1, false);
  console_output::fill_background("{_#FFFFFF}");

  // test menu
  vector<MENU_ITEM> menu_items;
  /*menu_items.push_back({"Menu item numero uno","{_#2aff00}",""});
  menu_items.push_back({"It's me a menu item","{_#428734}",""});
  menu_items.push_back({"Yaay! Hello!","{_#344187}",""});
  menu_items.push_back({"Suprise :P","{_#8c9eff}",""});*/
  for (int i = 0; i < 10; i++)
    menu_items.push_back(MENU_ITEM("Settings", "{#AAAAAA}", "{_#8c9eff}", "../Icons/Settings.bmp", "{#ffffff}", ' ',
                                   "{_#03b7a5}", 5));


  /* menu_items.push_back({"Tadaaaa!","{_#FF00FF}",""});
   menu_items.push_back({
     "I'm a sad menu item. My item caption is very long.. This is realy bad i thinkk :(","{_#ff3d63}",""
   });*/

  vector<MENU_ITEM_RECTANGLE> drawed_menu = console_output::draw_menu(menu_items, 20, 5, 3, true);

  // testing icon to ansii
  console_utils::set_console_cursor_pos({0, 0});
  // console_ascii::print_ascii_block(console_ascii::image_to_ascii_block("../Icons/Settings.bmp"));

  console_select::select_menu_item(drawed_menu);


  //console_output::print_line("Hello {#ff00ff}til");
  //console_output::print_separatorline("-");
  //console_output::print_rectangle({ {5,2},{10,7} }, "{_#00FF00}");
  /*

  console_output::print_line("Dies ist ein {#00FFFF}elendiger Satz.{;} {_#666666}YAY, grauer hintergrund");
  console_output::print_line("Hello til2");*/
  getchar();
  return 0;
}
