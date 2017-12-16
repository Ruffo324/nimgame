#include "stdafx.h"
#include "console_ascii.h"
#include <iostream>
#include "COLOR_STRUCT.h"
#include "console_color.h"
#include "console_utils.h"
#include "console_output.h"

console_handler::COLOR_STRUCT console_handler::console_ascii::transparent_color =
  console_handler::COLOR_STRUCT(255, 0, 255);

console_handler::ASCII_BLOCK console_handler::console_ascii::image_to_ascii_block(std::string filename)
{
  // call base function with space text_char.
  // space text_char is background only
  return image_to_ascii_block(filename, ' ');
}

console_handler::ASCII_BLOCK console_handler::console_ascii::image_to_ascii_block(std::string filename, char text_char)
{
  console_utils::set_console_cursor_pos({ 0,0 }); // debug

  //TODO: Parameter as filestream o something like this
  FILE* file;
  errno_t file_errno = fopen_s(&file, filename.c_str(), "rb");

  // read the 54-byte header
  unsigned char info[54];
  fread(info, sizeof(unsigned char), 54, file);

  const int width = *reinterpret_cast<int*>(&info[18]);
  const int height = *reinterpret_cast<int*>(&info[22]);

  const int row_padded = (width * 3 + 3) & (~3);
  unsigned char* data = new unsigned char[row_padded];

  // space text_char is background color
  const bool background_color = text_char == ' ';

  ASCII_BLOCK return_ascii_block = ASCII_BLOCK();

  // parse bitmap line by line
  for (int current_height = 0; current_height < height; current_height++)
  {
    std::string current_line = "";

    //TODO: Solution for last_color_struct
    COLOR_STRUCT last_color_struct = COLOR_STRUCT(0, 0, 0);

    fread(data, sizeof(unsigned char), row_padded, file);

    // and parse bitmap pixel by pixel per line
    for (int a = 0; a < width * 3; a += 3)
    {
      // data + x contains colors in B, G, R format
      const unsigned char tmp = data[a];
      COLOR_STRUCT color_struct = COLOR_STRUCT(int(data[a + 2]), int(data[a + 1]), int(data[a]));

      const bool transparent = color_struct.same_color(transparent_color);
      //TODO: retalkt with til
      const std::string current_text_char = transparent ? " " : (text_char == ' ' ? " " : text_char + "");

      if (color_struct.same_color(last_color_struct))
        current_line += current_text_char;
      else if (transparent)
        current_line += "{;}" + current_text_char;
      else
        current_line += console_color::color_struct_to_ansi(color_struct, COLOR_STRUCT(0, 0, 0), background_color) + current_text_char;

      // save last color_struct
      last_color_struct = transparent ? transparent_color : color_struct;
    }

    // push bitmap height line to text block
    return_ascii_block.text_block.push_back(current_line);
  }
  fclose(file);

  return return_ascii_block;
}

void console_handler::console_ascii::print_ascii_block(ASCII_BLOCK ascii_block)
{
  _COORD current_cursor_position = console_utils::get_console_cursor_position();
  for (int i = 0; i < ascii_block.text_block.size(); i++)
  {
    _COORD next_cursor_position = {current_cursor_position.X, current_cursor_position.Y + i};
    console_utils::set_console_cursor_pos(next_cursor_position);
    console_output::print_line(ascii_block.text_block[i]);
  }
}
