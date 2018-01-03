#pragma once
#include <string>

namespace sites
{
  class options
  {
  public:
    static std::string name_player_a;
    static std::string name_player_b;
    static void draw();
    static void change_player_names();
  };
}
