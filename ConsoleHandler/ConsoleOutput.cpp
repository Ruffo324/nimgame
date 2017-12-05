#include "stdafx.h"
#include "ConsoleOutput.h"
#include "ConsoleUtils.h"
#include "ConsoleTypes.h"
#include <string.h>

namespace console_handler
{
  /**
   * \brief Prints a line with the given text.
   * \brief Cuts the line in sub lines if the text is to long
   * \param message The message wich should be written to the console
   */
  void ConsoleOutput::print(console_types console_type, std::string message)
  {
    std::string consoleTypeText = console_utils::get_console_type_text(console_type);
    std::string out_message = consoleTypeText + " | " + message;
    printf("%s\n", out_message.c_str());
  }

  /**
   * \brief Prints a line the console
   * \param pattern The pattern for the line. Default = 
   */
  void ConsoleOutput::print_line(const console_types console_type, std::string pattern)
  {
    int console_witdh = console_utils::get_console_width();
    console_witdh -= console_utils::get_console_type_text(console_type).length() - 3;
    std::string print_str = "";

    for(int i = 0; i < console_witdh / pattern.length(); i++)
    {
      print_str += pattern;
    }
    print(console_type, "\n" + print_str);
  }
  
   /**  * \brief Displays a menu structure & returns the menu index  */    int ConsoleOutput::dipslay_menu(std::string menu_title, std::string[] menu_entrys)  {    // Write menu    print_line(menu, "-");    POINT cursor_position;    std::GetCursorPos(&cursor_position);    int menu_item_poss[menu_entrys.length];     for(int i = 0; i < menu_entrys.length; i++)    {      std::GetCursorPos(&cursor_position);      menu_item_poss[i] = cursor_position.y;      print(menu, i.c_str() + " - " +  menu_entrys[i].c_str());    }        print(menu, "Please select one entry. (arrow keys)");    print_line(menu, "-");        // Handle menu selection    int keyInput;    int currentItemIndex = menu_entrys.length;    std::SetCursorPos(0, menu_item_poss[currentItemIndex]);    while(keyInput != 13)    {      keyInput = getch();      switch(keyInput)      {        case KEY_UP:          currentItemIndex--;          if(currentItemIndex < 0)            currentItemIndex = menu_entrys.length;          break;        case KEY_DOWN:          currentItemIndex++;          if(currentItemIndex > menu_entrys.length)            currentItemIndex = 0;          break;      }      std::SetCursorPos(0, menu_item_poss[currentItemIndex]);    }        print(menu, "Selected: " + menu_entrys[currentItemIndex]);  }
}
