#pragma once
#include <vector>

namespace console_handler
{
  struct ASCII_BLOCK
  {
    std::vector<std::string> text_block;
    char original_char;
    std::string icon_filename;
  };
}
