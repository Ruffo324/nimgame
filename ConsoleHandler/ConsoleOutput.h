#pragma once
#include "ConsoleHandler.h"
#include <string>

namespace console_handler
{
   class ConsoleOutput
  {
  public:
    static CONSOLE_HANDLER_API void write(std::string message);
  private:
    ConsoleOutput();
    ~ConsoleOutput();
  };
}
