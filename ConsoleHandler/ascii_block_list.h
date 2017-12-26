#pragma once
#include <string>
#include <vector>
#include "ascii_block.h"

//TODO: fix warnings correctly
#pragma warning( disable: 4251 )

namespace console_handler
{
  class ascii_block_list
  {
  public:
    /**
     * \brief Contains an ascii block for each char.
     */
    std::vector<ascii_block> ascii_blocks;

    /**
     * \brief Contains the original string
     */
    std::string original_string;

    /**
     * \brief Contains the wanted font size
     */
    int font_size;

    /**
     * \brief Creates a new ascii block list.
     * \param string_value The text-string
     * \param font_size_value The wanted font size
     */
    ascii_block_list(std::string string_value, int font_size_value);
    void print();
  };
}
