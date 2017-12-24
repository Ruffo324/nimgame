#pragma once
#include "console_handler.h"

namespace console_handler
{
  /**
   * \brief The type of an ASCII_BLOCK struct.
   */
  enum CONSOLE_HANDLER_API ascii_block_type
  {
    /**
     * \brief The source type of the ascii block is an icon file
     */
    icon,

    /**
     * \brief The source type of the ascii block is an image file
     */
    image,

    /**
     * \brief The source type of the ascii block is an text char. 
     * \brief (Letter, number, special chars & everything else)
     */
    text_char
  };
}
