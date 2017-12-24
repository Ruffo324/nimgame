#pragma once
#include <vector>
#include "ascii_block_type.h"
#include <Windows.h>

namespace console_handler
{
  /**
   * \brief # Informations about the source. (Icon / Text char)
   * \brief # Text lines with color codes for print the wanted symbol / bitmap.
   * \brief Contains ascii smybol informations.
   */
  struct CONSOLE_HANDLER_API ASCII_BLOCK
  {
    /**
     * \brief Textlines with color codes and fillup chars
     */
    std::vector<std::string> text_block;

    /**
     * \brief Only used if the original content was an text char.
     * \brief Contains the original text char.
     */
    char original_char;

    /**
     * \brief Only used if the original content was an icon file.
     * \brief Contains the original icon file.
     */
    std::string icon_filename;

    /**
     * \brief The type of the source of the ascii block.
     */
    ascii_block_type ascii_block_type;

    /**
     * \brief The size of the ascii block
     */
    SIZE ascii_block_size;


    /**
     * \brief Creates a new char based ASCII block
     * \param text_block_value The textlines with color codes and fillup chars.
     * \param original_char_value The source char. (So, the "translated" text-char)
     */
    ASCII_BLOCK(const std::vector<std::string> text_block_value, const char original_char_value)
      : text_block(text_block_value), original_char(original_char_value), ascii_block_type(text_char)
    {
    }

    /**
    * \brief Creates a new icon file based ASCII block
    */
    ASCII_BLOCK(const std::string icon_filename_value)
      : original_char(0), icon_filename(icon_filename_value), ascii_block_type(icon)
    {

    }
  };
}
