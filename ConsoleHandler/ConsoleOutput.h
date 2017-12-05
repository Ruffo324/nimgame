#pragma once
#include "ConsoleHandler.h"
#include <string>
#include "ConsoleTypes.h"

namespace console_handler
{
   class ConsoleOutput
  {
  public:
    static CONSOLE_HANDLER_API void print(console_types console_type, std::string message);
    static CONSOLE_HANDLER_API void print_line(console_types console_type, std::string pattern);
  private:
    ConsoleOutput();
    ~ConsoleOutput();
  };
}
