#pragma once
#include "console_handler.h"
#include <vector>
#include "ASCII_BLOCK.h"

namespace console_handler
{
  class CONSOLE_HANDLER_API console_ascii
  {
  public:
    static ASCII_BLOCK create_ascii_char_text(char ascii_wanted_char, int height, int width);
    static std::vector<ASCII_BLOCK> transform_string_to_ascii_string(std::string to_transform_string, int height,
                                                                    int width);
    static ASCII_BLOCK image_to_ascii_block(std::string filename);
  };
}
