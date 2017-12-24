#pragma once
#include "console_handler.h"

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

    COLOR_STRUCT(const int red_value, const int green_value, const int blue_value)
      : red(red_value), green(green_value), blue(blue_value)
    {
    }


    /**
     * \brief Compares this color_struct with an other color struct.
     * \param compare_with The COLOR_STRUCT to compare with
     * \return true or false if the other color struct is the same
     */
    bool same_color(const COLOR_STRUCT compare_with) const
    {
      return compare_with.red == red && compare_with.green == green && compare_with.blue == blue;
    };
  };
}
