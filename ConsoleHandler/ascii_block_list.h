#pragma once
#include <string>
#include <vector>
#include "ascii_block.h"
#include "console_handler.h"

//TODO: fix warnings correctly
#pragma warning(disable: 4251)

namespace console_handler
{
  class ascii_block_list
  {
  public:
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
    CONSOLE_HANDLER_API ascii_block_list(std::string string_value, int font_size_value, const COLOR_STRUCT foreground_color_value);
    CONSOLE_HANDLER_API ascii_block_list(std::string string_value, int font_size_value);

    /**
     * \brief New ascii_block_list with input given string
     * \param font_size_value Font size
     */
    CONSOLE_HANDLER_API ascii_block_list(const int font_size_value);

    /**
     * \brief Toggles if the list should  be centered printed.
     * \param center Should the list get centerd on next print?
     * \param item_side_length The length of the box in where the list should get centered
     */
    void CONSOLE_HANDLER_API center_block_list(const bool center, const int item_side_length);
    void CONSOLE_HANDLER_API draw();
    void CONSOLE_HANDLER_API input(std::string background_color_string);

  private: 
    bool center_;
    int item_side_length_;
    void create_blocks();
    /**
    * \brief If not given, the color of the bitmap used. (Placeholder Color_struct)
    * \brief Forground color for the parsed bitmap.
    */
    COLOR_STRUCT foreground_color;
    /**
    * \brief Contains an ascii block for each char.
    */
    std::vector<ascii_block> ascii_blocks;

  };
}
