#pragma once
#include "console_handler.h"
#include <vector>
#include "ASCII_BLOCK.h"
#include "COLOR_STRUCT.h"
#include <Windows.h>

namespace console_handler
{
  class CONSOLE_HANDLER_API console_ascii
  {
  public:
    static std::vector<ascii_block> string_to_ascii_blocks(std::string, int size);
  };
}
