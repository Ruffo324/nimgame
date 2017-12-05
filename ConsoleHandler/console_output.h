#pragma once
#include "console_handler.h"
#include <string>
#include "console_type.h"

namespace console_handler
{
  class console_output
  {
  public:
    static CONSOLE_HANDLER_API void print(console_type console_type, std::string message);
    static CONSOLE_HANDLER_API void print_line(console_type console_type, std::string pattern);
  };
}
