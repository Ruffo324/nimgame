#include "stdafx.h"
#include "shape_rectangle.h"
#include "console_utils.h"
#include "console_output.h"

namespace console_handler
{
  void shape_rectangle::print()
  {
    // calculate recangle props
    const int lenght = right_.X - left_.X;
    const int height = left_.Y > right_.Y ? left_.Y - right_.Y : right_.Y - left_.Y;

    // calculate rectangle length
    std::string length_pattern = "";
    for (int i = 0; i < lenght; i++)
      length_pattern += text_char_;

    // add color code braces if not given
    if (color_string_.front() != '{')
      color_string_ = '{' + color_string_;
    if (color_string_.back() != '}')
      color_string_ += '}';

    // print rectangle
    for (int i = 0; i < height; i++)
    {
      console_utils::set_console_cursor_pos({left_.X, left_.Y + short(i)});
      console_output::print(color_string_ + length_pattern);
    }
  }

  _COORD shape_rectangle::get_left() const
  {
    return left_;
  }

  _COORD shape_rectangle::get_right() const
  {
    return right_;
  }

  shape_rectangle::shape_rectangle(const _COORD left, const _COORD right, const std::string color_string,
                                   const char text_char)
    : left_(left), right_(right), color_string_(color_string), text_char_(text_char)
  {
  }
}
