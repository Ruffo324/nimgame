// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleHandler.h"
#include <iostream>
#include "ConsoleOutput.h"

using namespace std;
using namespace console_handler;

int main()
{
  ConsoleOutput::write("Hello till"); 

  getchar();
    return 0;
}

