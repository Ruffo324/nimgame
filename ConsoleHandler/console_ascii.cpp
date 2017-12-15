#include "stdafx.h"
#include "console_ascii.h"
#include <iostream>

console_handler::ASCII_BLOCK console_handler::console_ascii::image_to_ascii_block(std::string filename)
{
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

  for (int current_height = 0; current_height < height; current_height++)
  {
    std::string current_line;
    fread(data, sizeof(unsigned char), row_padded, file);
    for (int current_width = 0; current_width < width * 3; current_width += 3)
    {
      // convert (B, G, R) to (R, G, B)
      const unsigned char tmp = data[current_width];
      data[current_width] = data[current_width + 2];
      data[current_width + 2] = tmp;

      // create hexadecimal value
      //cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
    }
  }

  fclose(file);

  ASCII_BLOCK return_ascii_block;

  return {};
}