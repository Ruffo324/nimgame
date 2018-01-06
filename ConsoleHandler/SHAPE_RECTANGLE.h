#pragma once
#include <Windows.h>
#include <string>

namespace console_handler
{
  class shape_rectangle
  {
  public: 
    void print();
    _COORD get_left() const;
    _COORD get_right() const;

    // constructor
    shape_rectangle(_COORD left, _COORD right, std::string color_string, const char text_char);

    // funcs
    void change_color_string(const std::string new_color_string);
  private:
    _COORD left_;
    _COORD right_;
    std::string color_string_;
    char text_char_;

  };
}
