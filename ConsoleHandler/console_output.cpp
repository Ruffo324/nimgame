#include "stdafx.h"
#include "console_output.h"
#include "console_utils.h"
#include "console_color.h"
#include <Windows.h>
#include <vector>
#include "MENU_ITEM_RECTANGLE.h"
#include "console_ascii.h"

namespace console_handler
{
  /**
   * \brief Prints the given text to the console.
   * \brief Parsing color codes to ansii color codes
   * \brief Cuts the line in sub lines if the text is to long
   * \param message The message wich should be written to the console
   */
  void console_output::print(const std::string message)
  {
    std::string out_message = message;

    out_message = console_color::parse_string_to_ansi_string(out_message);
    internal_write(out_message);
  }

  /**
   * \brief Resets the color at the cursor position
   */
  void console_output::reset_color()
  {
    print("{;}");
  }

  /**
  * \brief Prints the given text to the console with new line feed.
  * \brief Parsing color codes to ansii color codes
  * \brief Cuts the line in sub lines if the text is to long
  * \param message The message wich should be written to the console
  */
  void console_output::print_line(const std::string message)
  {
    std::string out_message = "{;}{#ffffff}" + message;

    out_message = console_color::parse_string_to_ansi_string(out_message);
    internal_write(out_message + "\n");
    //printf("%s\n", out_message.c_str());
  }

  /**
   * \brief Prints a line the console
   * \param pattern The pattern for the line. Default = 
   */
  void console_output::print_separatorline(std::string pattern)
  {
    const int console_witdh = console_utils::get_console_width();
    std::string print_str = "";

    for (unsigned int i = 0; i < console_witdh / pattern.length(); i++)
      print_str += pattern;

    const _COORD cursor_pos = console_utils::get_console_cursor_position();

    if (cursor_pos.X != 0)
      print_str = "\n" + print_str;

    print_line(print_str);
  }

  void console_output::print_rectangle(const SHAPE_RECTANGLE rectangle, std::string color_string, const char text_char)
  {
    const _COORD old_cursor_position = console_utils::get_console_cursor_position();

    // calculate recangle props
    const int lenght = rectangle.right.X - rectangle.left.X;
    const int height = rectangle.left.Y > rectangle.right.Y
                         ? rectangle.left.Y - rectangle.right.Y
                         : rectangle.right.Y - rectangle.left.Y;

    // calculate rectangle length
    std::string length_pattern = "";
    for (int i = 0; i < lenght; i++)
      length_pattern += text_char;

    // add color code braces if not given
    if (color_string.front() != '{')
      color_string = '{' + color_string;
    if (color_string.back() != '}')
      color_string += '}';

    // print rectangle
    for (int i = 0; i < height; i++)
    {
      console_utils::set_console_cursor_pos({rectangle.left.X, rectangle.left.Y + short(i)});
      print(color_string + length_pattern);
    }

    // reset to last cursor position
    console_utils::set_console_cursor_pos(old_cursor_position);
    print("");
  }

  void console_output::fill_background(const std::string color_string, const char text_char)
  {
    console_utils::set_console_cursor_pos({0,0});
    const int console_height = console_utils::get_console_height();
    const int console_width = console_utils::get_console_width();

    std::string line = color_string;
    for (int i = 0; i < console_width; i++)
      line += text_char;

    // fill background
    for (int i = 0; i < console_height; i++)
      print_line(line);
  }

  std::vector<MENU_ITEM_RECTANGLE> console_output::draw_menu(std::vector<MENU_ITEM> menu_items,
                                                             const int window_margin,
                                                             int margin_between_boxes, int boxes_per_row,
                                                             bool recalculate_per_row)
  {
    std::vector<MENU_ITEM_RECTANGLE> menu_item_rectangles;
    // Calculate box side lenght:
    // (min(console width , console height)
    // - (2 x window_margin [left & right])
    // - boxes per row - 1 [spaces only] * margin_between_boxes)
    // divide result by boxes_per_row = box side lenght
    const int boxes_per_column = int(menu_items.size()) / boxes_per_row;

    const int rest_console_width = console_utils::get_console_width()
      - (2 * window_margin) - (boxes_per_row - 1) * margin_between_boxes;
    const int rest_console_height = console_utils::get_console_height() -
      2 * window_margin - (boxes_per_column - 1) * margin_between_boxes;
    const bool box_lenght_by_height =
      console_utils::get_console_height() < console_utils::get_console_width();

    int box_side_length =
      box_lenght_by_height
        ? rest_console_height / boxes_per_column
        : rest_console_width / boxes_per_row;

    if (box_side_length < 1)
      box_side_length = 5;
    if (recalculate_per_row)
    {
      int i = 0;
      do
      {
        boxes_per_row = (rest_console_width / box_side_length) - i;
        i++;
      }
      while (boxes_per_row * box_side_length + ((boxes_per_row - 1) * margin_between_boxes) > rest_console_width);
    }

    const int left_extra_margin =
      box_lenght_by_height
        ? ((console_utils::get_console_width()
          - (box_side_length * boxes_per_row)
          - ((boxes_per_row - 1) * margin_between_boxes)
          - (2 * window_margin)) / 2)
        : 0;
    //- (box_side_length * boxes_per_row) - (boxes_per_row - 1) * margin_between_boxes) : 0;
    int current_row = 0;
    int current_row_index = 0;


    // calculate rectangles
    for (int i = 0; i < menu_items.size(); i++)
    {
      // create new item rectangle
      MENU_ITEM_RECTANGLE item_rectangle = MENU_ITEM_RECTANGLE(menu_items[i]);

      // item rectangle.left
      item_rectangle.item_rectangle.left.X =
        window_margin + left_extra_margin +
        + current_row_index * box_side_length
        + current_row_index * margin_between_boxes;
      item_rectangle.item_rectangle.left.Y =
        window_margin
        + current_row * box_side_length
        + current_row * margin_between_boxes;

      // item rectangle.rigth 
      item_rectangle.item_rectangle.right.X =
        item_rectangle.item_rectangle.left.X + box_side_length;
      item_rectangle.item_rectangle.right.Y =
        item_rectangle.item_rectangle.left.Y + (box_side_length);

      // position in menu
      item_rectangle.menu_row = current_row;
      item_rectangle.menu_row_index = current_row_index;

      // add to vector
      menu_item_rectangles.push_back(item_rectangle);

      // next row index
      current_row_index++;

      // Begin a new row?
      if ((i + 1) % boxes_per_row == 0)
      {
        current_row++;
        current_row_index = 0;
      }
    }

    // draw boxes
    for (int i = 0; i < menu_item_rectangles.size(); i++)
    {
      // print rectangle background
      print_rectangle(menu_item_rectangles[i].item_rectangle,
                      menu_item_rectangles[i].menu_item.item_background);

      //TODO: Adding  ascii caption and calculate text_height
      const int text_height = 30;
      const int offset = menu_item_rectangles[i].menu_item.border_size + 10;
      //print icon
      const SIZE icon_size = {
        box_side_length - (offset * 2),
        box_side_length - ((offset * 2) + text_height)
          };
      console_utils::set_console_cursor_pos({
        menu_item_rectangles[i].item_rectangle.left.X + short(offset),
        menu_item_rectangles[i].item_rectangle.left.Y + short(offset)
      });
      console_ascii::print_ascii_block(console_ascii::image_to_ascii_block("../Icons/Settings.bmp", icon_size));
    }
    return menu_item_rectangles;
  }

  void console_output::internal_write(std::string message)
  {
    const std::string reset_ansi_string = "\x1B[0m";
    const std::string ansi_start_string = "\x1B[";
    // save cursor position
    _COORD current_cursor = console_utils::get_console_cursor_position();
    std::string print_string = "";
    bool reset_active = false;

    for (int i = 0; i < message.length(); i++)
    {
      print_string += message[i];
      if (reset_active && print_string.length() >= ansi_start_string.length())
        if (print_string.substr(print_string.length() - ansi_start_string.length()) == ansi_start_string)
        {
          int cursor_steps = int(print_string.length() - ansi_start_string.length());
          console_utils::set_console_cursor_pos({current_cursor.X + short(cursor_steps), current_cursor.Y});
          print_string = ansi_start_string;
          reset_active = false;
        }

      if (print_string.length() >= reset_ansi_string.length())
        if (print_string.substr(print_string.length() - reset_ansi_string.length()) == reset_ansi_string)
        {
          reset_active = true;
          print_string = print_string.substr(0, print_string.length() - reset_ansi_string.length());
          printf("%s", print_string.c_str());
          current_cursor = console_utils::get_console_cursor_position();
          print_string = "";
        }
    }
    if (!reset_active && print_string.length() > 0)
      printf("%s", print_string.c_str());
  }
}
