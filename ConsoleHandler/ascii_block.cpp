#include "stdafx.h"
#include "ascii_block.h"
#include "console_color.h"
#include "console_utils.h"
#include "console_output.h"
#include "console_bmp.h"

namespace console_handler
{
  ascii_block::ascii_block(const std::string bitmap_path_value, const SIZE size_value)
    : original_char(0), text_char(' '), bitmap_path(bitmap_path_value), ascii_block_type(icon),
      ascii_block_size(size_value)
  {
    generate_text_lines();
  }

  ascii_block::ascii_block(const std::string bitmap_path_value, const SIZE size_value, const char text_char_value)
    : original_char(0), text_char(text_char_value), bitmap_path(bitmap_path_value), ascii_block_type(icon),
      ascii_block_size(size_value)
  {
    generate_text_lines();
  }

  ascii_block::ascii_block(const char text_char_value, const SIZE size_value)
    : original_char(text_char_value), text_char(' '), ascii_block_size(size_value)
  {
    console_bmp text_bitmap = console_bmp(ascii_block_size.cx, ascii_block_size.cy);
    text_bitmap.write_text(original_char);

    // build bitmap path
    bitmap_path = "../Icons/Chars/";
    bitmap_path.push_back(original_char);
    bitmap_path += "_";
    bitmap_path += std::to_string(ascii_block_size.cx);
    bitmap_path += +".bmp";
    // save bitmap
    text_bitmap.save(bitmap_path.c_str());
    print(); //debug
  }

  void ascii_block::print()
  {
    const _COORD current_cursor_position = console_utils::get_console_cursor_position();
    for (short i = 0; i < text_lines.size(); i++)
    {
      const _COORD next_cursor_position = {
        current_cursor_position.X,
        current_cursor_position.Y + i
      };
      console_utils::set_console_cursor_pos(next_cursor_position);
      console_output::print_line(text_lines[i]);
    }
  }

  void ascii_block::generate_text_lines()
  {
    // wanted height | wanted width not even = make it even.
    const int wanted_width = ascii_block_size.cx % 2 == 0 ? ascii_block_size.cx : ascii_block_size.cx + 1;
    const int wanted_height = ascii_block_size.cy % 2 == 0 ? ascii_block_size.cy : ascii_block_size.cy + 1;

    FILE* file;
    //TODO: adding error handling
    errno_t file_errno = fopen_s(&file, bitmap_path.c_str(), "rb");

    // read the 54-byte header
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file);

    const int width = *reinterpret_cast<int*>(&info[18]);
    const int height = *reinterpret_cast<int*>(&info[22]);

    // Throw exception if file size is bigger than wanted size
    if (width < wanted_width || height < wanted_height)
      throw "Wanted icon size is bigger than given icon size!";

    const int row_padded = (width * 3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];

    // space text_char is background color
    const bool background_color = text_char == ' ';

    // parse bitmap line by line
    for (int current_height = 0; current_height < height; current_height++)
    {
      std::string current_line = "";

      //TODO: Solution for last_color_struct
      COLOR_STRUCT last_color_struct = COLOR_STRUCT(0, 0, 0);

      fread(data, sizeof(unsigned char), row_padded, file);

      // Simple "resize"
      if (current_height % (height / wanted_height) != 0)
        continue;

      // and parse bitmap pixel by pixel per line
      for (int a = 0; a < width * 3; a += 3)
      {
        // Simple "resize"
        if (a % ((width * 3) / wanted_width) != 0)
          continue;

        // data + x contains colors in B, G, R format
        COLOR_STRUCT color_struct = COLOR_STRUCT(int(data[a + 2]), int(data[a + 1]), int(data[a]));

        const bool transparent = color_struct.same_color(transparent_color);

        //TODO: retalkt with til
        const std::string current_text_char = transparent ? " " : (text_char == ' ' ? " " : text_char + "");

        if (color_struct.same_color(last_color_struct))
          current_line += current_text_char;
        else if (transparent)
          current_line += console_color::color_code_to_ansi(";", COLOR_STRUCT(0, 0, 0)) + current_text_char;
        else
          current_line += console_color::color_struct_to_ansi(color_struct, COLOR_STRUCT(0, 0, 0), background_color) +
            current_text_char;

        // save last color_struct
        last_color_struct = transparent ? transparent_color : color_struct;
      }

      // push bitmap height line to text block
      text_lines.push_back(current_line);
    }
    fclose(file);
  }

  void ascii_block::char_bitmap_creation()
  {
  }
}
