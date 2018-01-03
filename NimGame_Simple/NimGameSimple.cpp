// "NimGameSimple.cpp": Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "console_handler.h"
#include "console_utils.h"
#include "main_menu.h"
#include "console_color.h"
#include "console_output.h"


int main()
{
  console_handler::console_utils::set_console_size(400, 400, true);
  console_handler::console_handler_core::prepare_console(15, false);
  console_handler::console_output::fill_background("{#E3F2FD}");

  // draw main menu
  main_menu::show_main_menu();
}







