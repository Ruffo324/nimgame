// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <console_handler.h>
#include <iostream>
#include "console_output.h"

using namespace std;
using namespace console_handler;

int main()
{
  console_handler_core::prepare_console();

  console_output::print(info, "Hello {#ff00ff}til");
  console_output::print_line(menu, "-");
  console_output::print(info, "Dies ist ein {#00FFFF}elendiger Satz.{;} {_#666666}YAY, grauer hintergrund");
  console_output::print(info, "Hello til2");
  getchar();
    return 0;
}

