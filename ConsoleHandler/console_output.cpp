#include "stdafx.h"
#include "console_output.h"
#include "console_utils.h"
#include "console_color.h"
#include <Windows.h>
#include <vector>

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
    std::string out_message = "{;}{#ffffff}" + message;

    out_message = console_color::parse_string_to_ascii_string(out_message);
    printf("%s", out_message.c_str());
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

    out_message = console_color::parse_string_to_ascii_string(out_message);
    printf("%s\n", out_message.c_str());
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
    const int height = rectangle.left.Y > rectangle.right.Y ? rectangle.left.Y - rectangle.right.Y : rectangle.right.Y - rectangle.left.Y;

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
    for(int i = 0; i < height; i++)
    {
      console_utils::set_console_cursor_pos({ rectangle.left.X, rectangle.left.Y + short(i)});
      print(color_string + length_pattern);
    }

    // reset to last cursor position
    console_utils::set_console_cursor_pos(old_cursor_position);
    print("");
  }

  void console_output::fill_background(const std::string color_string, const char text_char)
  {
    const _COORD old_console_cursor_postion = console_utils::get_console_cursor_position();
    console_utils::set_console_cursor_pos({ 0,0 });
    const int console_height = console_utils::get_console_height();
    const int console_width = console_utils::get_console_width();

    std::string line = color_string;
    for (int i = 0; i < console_width; i++)
      line += text_char;

    // fill background
    for (int i = 0; i < console_height; i++)
      print_line(line);

    // reset to old cursor position
    console_utils::set_console_cursor_pos(old_console_cursor_postion);
  }

  int console_output::draw_menu(std::vector<MENU_ITEM> menu_items)
  {
    const int margin = 10;
    const int space_between_boxes = 5;

    int console_width = console_utils::get_console_width();


    std::vector<SHAPE_RECTANGLE> menu_item_boxes;
    int box_width = 0;
    int boxes_per_row = 1;


    for (int i = 1; i < menu_items.size(); i++)
    {
      box_width = (console_width - (2 * margin)) / i;
      if (i - (space_between_boxes * (i - 1)) > 0)
        boxes_per_row = i - 1;
      else
        break;
    }

    int current_row = 0;
    int current_collum = 0;
    // calculate boxes
    for (int i = 0; i < menu_items.size(); i++)
    {
      // Calculate current collum
      if ((i + 1 / boxes_per_row) % 2 != 0)
        current_collum++;
      else
        current_collum = 0;

      SHAPE_RECTANGLE menu_item_box = {
        {
          margin + (box_width * current_row) == 0 ? 0 : space_between_boxes,
          margin + (box_width * current_collum) == 0 ? 0 : space_between_boxes
        } };
      menu_item_box.right = { short(menu_item_box.left.X + box_width), short(menu_item_box.left.Y + box_width )};
      menu_item_boxes.push_back(menu_item_box);

      if ((i + 1 / boxes_per_row) % 2 == 0)
        current_row++;
    }

    // draw boxes
    for (int i = 0; i < menu_item_boxes.size(); i++)
    {
      print_rectangle(menu_item_boxes[i], "{_#d86711}");
    }
    return 1;
  }
}
