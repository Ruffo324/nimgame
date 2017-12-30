#pragma once
#include "stdafx.h"
#include "console_handler.h"
#include <fstream>

namespace console_handler
{
  struct CONSOLE_HANDLER_API COLOR_STRUCT
  {
    /**
     * \brief Value of the red color part
     */
    int red;

    /**
    * \brief Value of the green color part
    */
    int green;

    /**
    * \brief Value of the blue color part
    */
    int blue;

    /**
     * \brief Means: Each color value is -1.
     * \brief Is this color struct an placeholder color?
     */
    bool placeholder;

    /**
     * \brief Creates an new color struct.
     * \param red_value Red value. (0-255)
     * \param green_value Green value. (0-255)
     * \param blue_value Blue value. (0-255)
     */
    COLOR_STRUCT(const int red_value, const int green_value, const int blue_value)
      : red(red_value), green(green_value), blue(blue_value), placeholder(false)
    {
    }


    /**
     * \brief Creates black color_struct.
     */
    COLOR_STRUCT()
      : red(0), green(0), blue(0), placeholder(false)
    {
    }

    /**
     * \brief Creates an new placeholder color_struct, or an color struct with 0, 0, 0
     * \param placeholder_value If true, colorstruct is placeholder (-1,-1,-1), else (0,0,0)
     */
    explicit COLOR_STRUCT(const bool placeholder_value)
      : red(0), green(0), blue(0), placeholder(placeholder_value)
    {
      if (placeholder)
      {
        red = -1;
        green = -1;
        blue = -1;
      }
    }

    /**
     * \brief Creates a new color_struct from a color_code string
     * \param color_code_string The color_code string that should be translated
     */
    explicit COLOR_STRUCT(std::string color_code_string)
      : red(0), green(0), blue(0), placeholder(false)
    {
      // Not valid hex string -> throw exception;
      if (color_code_string[0] != '#' && color_code_string[1] != '#' && color_code_string[2] != '#')
        throw std::invalid_argument("Color code must start with a #!");

      // Parse clean color code
      std::string clean_color_code;
      for (unsigned int i = 0; i < color_code_string.length(); i++)
      {
        if (color_code_string[i] != '#' && color_code_string[i] != '_'
          && color_code_string[i] != '{' && color_code_string[i] != '}')
          clean_color_code += color_code_string[i];
      }

      // Parse colors from hex code
      sscanf_s(clean_color_code.c_str(), "%02x%02x%02x",
               &red, &green, &blue);
    }

    /**
     * \brief Compares this color_struct with an other color struct.
     * \param compare_with The COLOR_STRUCT to compare with
     * \return true or false if the other color struct is the same
     */
    bool same_color(const COLOR_STRUCT compare_with) const
    {
      return compare_with.red == red
        && compare_with.green == green
        && compare_with.blue == blue
        && compare_with.placeholder == placeholder;
    };
  };
}
