#pragma once
#include <Windows.h>
#include <xstring>

namespace console_handler
{
  class console_bmp
  {
  public:
    console_bmp(int width, int height);
    void write_text(const char char_value);
    bool save(const char* filename);
    ~console_bmp();
  private:

    int width;
    int height;
    unsigned char** data_;
    HBITMAP bitmap_handle;
    HBITMAP getHandle();
    COLORREF getPixel(int x, int y);
    void setPixel(int x, int y, COLORREF color);
    HFONT getFont(const char* name, int size, bool italic, bool bold, bool underline, bool strike_out);
    console_bmp(std::string text);
    console_bmp(std::string text, SIZE size);
  };
}
