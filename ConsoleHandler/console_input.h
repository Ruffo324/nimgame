#pragma once
#include "console_handler.h"

namespace console_handler
{

  class console_input
  {
  public:
    static CONSOLE_HANDLER_API void start_async_input_fetching();

  private:
    static void async_input_fetching();
  };
}

