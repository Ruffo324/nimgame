#pragma once
#include <string>
#include <vector>

namespace sites
{
  class options
  {
  public:
    // Variable settings
    static std::string name_player_a;
    static std::string name_player_b;
    static std::vector<int> field_structure;
    static int max_allowed_per_row;

    // Fix settings
    static int window_margin;
    static std::string site_background;
    static std::string item_border_color;
    static std::string grid_caption_color;
    static int grid_caption_font_size;
    static int border_size;
    static int max_cols;
    static int max_rows;

    static void draw();
    static void change_field_size_step_row();
    static void change_field_size_step_cols(const int rows);
    static void change_player_names();

  };
}
