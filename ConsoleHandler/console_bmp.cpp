#include "stdafx.h"
#include "console_bmp.h"


#include <Windows.h>
#include <iostream>
#include <fstream>

namespace console_handler
{
  console_bmp::console_bmp(int width, int height)
  {
    int i, line_size;
    BITMAPINFO bih = { 0 };
    HDC hdc;

    if (width < 1 || height < 1)
    {
      throw new std::invalid_argument("Invalid image size.");
    }

    this->width = width;
    this->height = height;

    try
    {
      this->data_ = new unsigned char*[height];
    }
    catch (std::bad_alloc&)
    {
      throw new std::string("Allocation for image rows failed.");
    }

    bih.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bih.bmiHeader.biWidth = width;
    bih.bmiHeader.biHeight = height;
    bih.bmiHeader.biPlanes = 1;
    bih.bmiHeader.biBitCount = 24;
    bih.bmiHeader.biCompression = BI_RGB;

    hdc = CreateCompatibleDC(0);
    this->bitmap_handle = CreateDIBSection(hdc, &bih, DIB_RGB_COLORS, (void**)&this->data_[0], 0, 0);
    DeleteDC(hdc);

    if (!this->bitmap_handle)
    {
      delete[] this->data_;
      throw new std::string("Allocation of DIB section failed.");
    }

    if ((width) % 4)
      line_size = 3 * width + (4 - (width * 3) % 4);
    else
      line_size = 3 * width;

    for (i = 1; i < height; i++)
      this->data_[i] = &this->data_[0][line_size * i];
  }

  console_bmp::~console_bmp()
  {
    DeleteObject(this->bitmap_handle);
    delete[] this->data_;
  }

  COLORREF console_bmp::getPixel(int x, int y)
  {
    if (x < 0 || x >= this->width)
    {
      throw new std::invalid_argument("x value out of bounds.");
    }

    if (y < 0 || y >= this->height)
    {
      throw new std::invalid_argument("y value out of bounds.");
    }

    return RGB(this->data_[y][3 * x + 2], this->data_[y][3 * x + 1], this->data_[y][3 * x]);
  }

  void console_bmp::setPixel(int x, int y, COLORREF color)
  {
    if (x < 0 || x >= this->width)
    {
      throw new std::invalid_argument("x value out of bounds.");
    }

    if (y < 0 || y >= this->height)
    {
      throw new std::invalid_argument("y value out of bounds.");
    }

    this->data_[y][3 * x] = GetBValue(color);
    this->data_[y][3 * x + 1] = GetGValue(color);
    this->data_[y][3 * x + 2] = GetRValue(color);
  }

  bool console_bmp::save(const char* filename)
  {
    std::ofstream* fout;
    BITMAPFILEHEADER bfh = { 0 };
    BITMAPINFOHEADER bih = { 0 };
    RGBQUAD rgbq = { 0 };
    int line_size;

    if (!filename)
    {
      throw new std::invalid_argument("filename is null.");
    }

    if ((this->width) % 4)
      line_size = 3 * this->width + (4 - (this->width * 3) % 4);
    else
      line_size = 3 * this->width;

    bfh.bfType = MAKEWORD('B', 'M');
    bfh.bfSize = sizeof(BITMAPFILEHEADER)
      + sizeof(BITMAPINFOHEADER)
      + sizeof(RGBQUAD)
      + this->height * line_size;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER)
      + sizeof(BITMAPINFOHEADER)
      + sizeof(RGBQUAD);

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = this->width;
    bih.biHeight = this->height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;

    fout = new std::ofstream(filename, std::ios::out | std::ios::binary);
    if (fout->fail())
    {
      delete fout;
      return false;
    }

    fout->write((const char *)&bfh, sizeof(BITMAPFILEHEADER));
    fout->write((const char *)&bih, sizeof(BITMAPINFOHEADER));
    fout->write((const char *)&rgbq, sizeof(RGBQUAD));
    fout->write((const char *)this->data_[0], line_size * this->height);

    if (fout->fail() || fout->bad())
    {
      fout->close();
      return false;
    }
    else
    {
      fout->close();
      return true;
    }
  }


  HFONT console_bmp::getFont(const char* name, int size, bool italic = false, bool bold = false, bool underline = false,
    bool strike_out = false)
  {
    LOGFONT lfont = { 0 };

    lfont.lfQuality = CLEARTYPE_QUALITY;
    lfont.lfCharSet = DEFAULT_CHARSET;

    strncpy_s(wchar(lfont.lfFaceName, name, 31);
    lfont.lfHeight = -size;
    if (italic) lfont.lfItalic = TRUE;
    if (bold) lfont.lfWeight = FW_BOLD;
    if (underline) lfont.lfUnderline = TRUE;
    if (strike_out) lfont.lfStrikeOut = TRUE;

    return CreateFontIndirect(&lfont);
  }

  void console_bmp::write_text(const char char_value)
  {
    // create device context for painting
    HDC hdc = CreateCompatibleDC(NULL);

    // select bitmap into DC
    const HBITMAP hbm_old = static_cast<HBITMAP>(SelectObject(hdc, this->bitmap_handle));

    // define rect for painting
    RECT rect = { 0,0,this->width, this->height };

    // draw white background
    FillRect(hdc, &rect, WHITE_BRUSH);

    // create and select font
    HFONT font = getFont("Arial Black", 40, false, true, true);
    HFONT font_old = (HFONT)SelectObject(hdc, font);

    // set text color and background mode
    SetTextColor(hdc, RGB(255, 0, 128));
    SetBkMode(hdc, TRANSPARENT);

    // draw centered text
    DrawText(hdc, reinterpret_cast<LPCWSTR>(char_value), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // replace DC bitmap and font by original one
    SelectObject(hdc, font_old);
    SelectObject(hdc, hbm_old);

    // free font and device context
    DeleteObject(font);
    DeleteDC(hdc);

    // save image
    this->save("test.bmp");

    // clean up
    delete this;
  }
}