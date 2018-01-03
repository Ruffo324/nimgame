#include "stdafx.h"
#include "ascii_block.h"
#include "console_color.h"
#include "console_utils.h"
#include "console_output.h"
#include "console_bmp.h"
#include <filesystem>

namespace console_handler
{
  ascii_block::ascii_block(const std::string bitmap_path_value, const SIZE size_value)
    : original_char(0), text_char(' '), bitmap_path(bitmap_path_value), ascii_block_type(icon),
    ascii_block_size(size_value), foreground_color(COLOR_STRUCT(true))
  {
    generate_text_lines();
  }

  ascii_block::ascii_block(const std::string bitmap_path_value, const SIZE size_value, const char text_char_value)
    : original_char(0), text_char(text_char_value), bitmap_path(bitmap_path_value), ascii_block_type(icon),
    ascii_block_size(size_value), foreground_color(COLOR_STRUCT(true))
  {
    generate_text_lines();
  }

  ascii_block::ascii_block(const std::string bitmap_path_value, const SIZE size_value,
    const COLOR_STRUCT foreground_color_value)
    : original_char(0), text_char(' '), bitmap_path(bitmap_path_value), ascii_block_type(icon),
    ascii_block_size(size_value), foreground_color(foreground_color_value)
  {
    generate_text_lines();
  }

  ascii_block::ascii_block(const std::string bitmap_path_value, const SIZE size_value,
    const char text_char_value, const COLOR_STRUCT foreground_color_value)
    : original_char(0), text_char(text_char_value), bitmap_path(bitmap_path_value), ascii_block_type(icon),
    ascii_block_size(size_value), foreground_color(foreground_color_value)
  {
    generate_text_lines();
  }

  ascii_block::ascii_block(const char text_char_value, const int font_size_value,
    const COLOR_STRUCT foreground_color_value)
    : original_char(text_char_value), text_char(' '), ascii_block_type(ascii_block_type::text_char),
    ascii_block_size({ font_size_value, font_size_value }), foreground_color(foreground_color_value)
  {
    // build bitmap path
    bitmap_path = "../Icons/Chars/";
    bitmap_path.push_back(original_char);

    if (IsCharUpper(original_char))
      bitmap_path += "_UP";

    bitmap_path += "_";
    bitmap_path += std::to_string(ascii_block_size.cx);
    bitmap_path += +".bmp";

    // Create bitmap if not existing
    if (!bitmap_exists())
    {
      console_bmp text_bitmap = console_bmp(ascii_block_size.cx, ascii_block_size.cy);
      text_bitmap.write_text(original_char);

      // save bitmap
      text_bitmap.save(bitmap_path.c_str());
    }

    generate_text_lines();
    // clean up
    //delete &text_bitmap;
  }

  void ascii_block::add_padding(const int padding)
  {
    padding_ += padding;
  }

  void ascii_block::draw()
  {
    const _COORD current_cursor_position = console_utils::get_console_cursor_position();

    // Icons can get manually sized lower
    short center_offset = 0;
    short center_offset_top = 0;
    if (this->ascii_block_type != ascii_block_type::text_char)
    {
      center_offset = short((ascii_block_size.cx - real_width_) / 2) + short(padding_ / 2);
      center_offset_top = short((ascii_block_size.cy - text_lines.size()) / 4);
    }

    for (short i = 0; i < text_lines.size(); i++)
    {
      const _COORD next_cursor_position = {
        current_cursor_position.X + center_offset,
        current_cursor_position.Y + i + center_offset_top
      };
      console_utils::set_console_cursor_pos(next_cursor_position);

      // Skip printing of empty lines
      if (text_lines[i] != "")
        console_output::print_line(text_lines[i]);
    }
  }

  void ascii_block::generate_text_lines()
  {
    const bool is_text_char = this->ascii_block_type == ascii_block_type::text_char;

    int wanted_width = !is_text_char && (ascii_block_size.cx % 2) != 0 ? ascii_block_size.cx : ascii_block_size.cx - 1;
    int wanted_height = !is_text_char && (ascii_block_size.cy % 2) != 0 ? ascii_block_size.cy : ascii_block_size.cy - 1;

    //TODO: adding error handling
    FILE* file;
    errno_t file_errno = fopen_s(&file, bitmap_path.c_str(), "rb");

    // read the 54-byte header
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file);

    const int width = *reinterpret_cast<int*>(&info[18]);
    const int height = *reinterpret_cast<int*>(&info[22]);

    // Correct size for resize.. 
    //TODO: make real resize
    if (!is_text_char)
    {
      while (int(round(double(width) / double(wanted_width))) == 2)
        wanted_width--;

      while (int(round(double(height) / double(wanted_height))) == 2)
        wanted_height--;
    }

    // Throw exception if file size is bigger than wanted size
    if (width < wanted_width || height < wanted_height)
      throw std::invalid_argument("Wanted icon size is bigger than given icon size!");

    const int row_padded = (width * 3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];

    // space text_char is background color
    const bool background_color = text_char == ' ';

    // parse bitmap line by line
    for (int current_height = 0; current_height < height; current_height++)
    {
      bool transparent_only = true;
      std::string current_line = "";

      //TODO: Solution for last_color_struct
      COLOR_STRUCT last_color_struct = COLOR_STRUCT(true);

      fread(data, sizeof(unsigned char), row_padded, file);

      // Simple "resize"
      if (current_height % int(round(double(height) / double(wanted_height))) != 0)
        continue;

      // Bitmap offset course of space on created bitmaps with chars
      int offset_left_right = (is_text_char ? int((wanted_width / 4)) : 0) * 3;
      if (offset_left_right == 3)
        offset_left_right += offset_left_right;

      // and parse bitmap pixel by pixel per line
      int line_content_width = 0;
      for (int a = 0 + offset_left_right; a < (width * 3 - offset_left_right); a += 3)
      {
        // Simple "resize"
        if (int(a / 3) % int(round(double(width) / double(wanted_width))) != 0)
          continue;

        COLOR_STRUCT color_struct = COLOR_STRUCT(0, 0, 0);
        // data + x contains colors in B, G, R format or RBG format
        if (is_text_char)
          color_struct = COLOR_STRUCT(int(data[a + 1]), int(data[a + 2]), int(data[a]));
        else
          color_struct = COLOR_STRUCT(int(data[a + 2]), int(data[a + 1]), int(data[a]));

        const bool transparent = color_struct.same_color(transparent_color);
        if (!transparent && transparent_only)
          transparent_only = false;

        // Foreground color given & not transparent -> use foreground color
        if (!transparent && !foreground_color.placeholder)
          color_struct = foreground_color;

        //TODO: retalkt with til
        const std::string current_text_char = transparent ? " " : (text_char == ' ' ? " " : text_char + "");

        if (color_struct.same_color(last_color_struct))
          current_line += current_text_char;
        else if (transparent)
          current_line += console_color::color_code_to_ansi(";", COLOR_STRUCT(0, 0, 0)) + current_text_char;
        else
          current_line += console_color::color_struct_to_ansi(color_struct, color_struct, background_color) +
          current_text_char;

        // save last color_struct
        last_color_struct = transparent ? transparent_color : color_struct;

        if (!transparent || !transparent_only)
          line_content_width++;
      }
      // 
      real_width_ = real_width_ < line_content_width ? line_content_width : real_width_;

      text_lines.insert(text_lines.begin(), transparent_only ? "" : current_line);
    }
    fclose(file);
  }

  bool ascii_block::bitmap_exists() const
  {
    struct stat buffer;
    return (stat(bitmap_path.c_str(), &buffer) == 0);
  }
}
