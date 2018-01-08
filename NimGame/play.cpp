#include "stdafx.h"
#include "play.h"
#include "console_output.h"
#include "options.h"
#include "console_utils.h"
#include "ascii_block_list.h"
#include "main.h"

namespace sites
{
  // static variables
  console_handler::dynamic_grid play::current_session_field_;
  std::string play::background_color_ = "{_#FFFFFF}";
  std::string play::text_value_color_ = "{#4CAF50}";
  std::string play::caption_color_ = "{#424242}";
  bool play::player_a_is_ = false;
  int play::current_selected_ = 0;
  int play::current_picked_ = 0;
  int play::current_remaining_ = 0;

  _COORD play::current_player_cursor_pos_;
  _COORD play::selected_cursor_pos_;
  _COORD play::picked_cursor_pos_;
  _COORD play::remaining_cursor_pos_;

  int play::font_size_;


  void play::gameplay()
  {
    draw_picked(current_picked_, current_picked_);
    draw_remaining(current_remaining_, current_remaining_);

    do {
      // Change player
      player_a_is_ = !player_a_is_;

      // Draw current player
      draw_current_player(player_a_is_ ? options::name_player_a : options::name_player_b, player_a_is_ ? options::name_player_b : options::name_player_a);

      // draw selected to 0
      draw_selected(0, current_selected_);
      current_selected_ = 0;

      std::vector<int> selected_by_current_user =
        current_session_field_.mark_and_select(true, options::max_allowed_per_row, "{_#1976D2}", "{_#64B5F6}", true);

      // disable items
      for (int i = 0; i < selected_by_current_user.size(); i++)
        current_session_field_.disable_item(selected_by_current_user[i], "{_#757575}", "{_#9E9E9E}");

      // draw picked
      current_picked_ += int(selected_by_current_user.size());
      draw_picked(current_picked_, current_picked_ - int(selected_by_current_user.size()));

      // draw remaining
      current_remaining_ -= int(selected_by_current_user.size());
      draw_remaining(current_remaining_, current_remaining_ + int(selected_by_current_user.size()));


    } while (!current_session_field_.all_items_disabled());

    // Current player winns
    win_screen();
  }

  void play::new_game()
  {
    //TODO: Make pretty game-color design
    console_handler::console_output::fill_background(background_color_);

    // reset game variables
    player_a_is_ = false;
    current_selected_ = 0;
    current_picked_ = 0;
    current_remaining_ = 0;

    generate_field();
    current_session_field_.draw();

    draw_statistics();
    gameplay();
  }

  void play::generate_field()
  {
    std::vector<console_handler::grid_item> field_items;
    int* current_selected_pointer = &current_selected_;
    auto* draw_selected_pointer = &draw_selected;

    // Get max items per row given
    int max_items_per_row = 0;
    for (int row = 0; row < options::field_structure.size(); row++)
    {
      if (max_items_per_row < options::field_structure[row])
        max_items_per_row = options::field_structure[row];
    }

    for (int row = 0; row < options::field_structure.size(); row++)
    {
      for (int field_item = 1; field_item <= max_items_per_row; field_item++)
      {
        // THE TIME IS RUNNING AWAY!
        //TODO: testing center boxes (MAKE THIS LATER @ME(CG))

        bool disiabled_item = false;
        if (field_item > options::field_structure[row])
          disiabled_item = true;

        // count all items
        if (!disiabled_item)
          current_remaining_++;

        console_handler::grid_item new_field_item =
          console_handler::grid_item(
            [current_selected_pointer, draw_selected_pointer](bool selected) mutable -> void {
          int old_selected = *current_selected_pointer;
          if (selected)
            *current_selected_pointer += 1;
          else
            *current_selected_pointer -= 1;

              draw_selected_pointer(*current_selected_pointer, old_selected);
        }, "", "{_#FDD835}", "../Icons/FireMatch.bmp", "{_#D84315}", ' ', "{_#37474F}", 5);

        new_field_item.disabled = disiabled_item;
        new_field_item.visible = !disiabled_item;
        field_items.push_back(new_field_item);
      }
    }
    current_session_field_ = console_handler::dynamic_grid("{#43A047}Good {#2E7D32}luck!", 30, field_items, options::window_margin, 5, max_items_per_row);
  }

  void play::draw_statistics()
  {
    const bool on_right_side = console_handler::console_utils::get_console_height() < console_handler::console_utils::get_console_width();
    const SIZE field_size = current_session_field_.get_full_size();
    int free_space = 0;

    if (on_right_side)
      free_space = console_handler::console_utils::get_console_width() - (field_size.cx + (2 * options::window_margin));
    else
      free_space = console_handler::console_utils::get_console_height() - (field_size.cy + (2 * options::window_margin));

    const _COORD start_cord = {
      short(on_right_side ? console_handler::console_utils::get_console_width() - free_space : options::window_margin),
      short(on_right_side ? options::window_margin + 30 : console_handler::console_utils::get_console_height() - free_space)
    };

    // calculate font size from the free space
    font_size_ = free_space / 15;
    const int caption_font_size = font_size_;
    console_handler::console_utils::set_console_cursor_pos(start_cord);

    // Current player caption
    console_handler::ascii_block_list current_player_caption = console_handler::ascii_block_list(caption_color_ + "Current Player:", caption_font_size);
    current_player_caption.draw();

    // Remember player name position
    current_player_cursor_pos_ = { console_handler::console_utils::get_console_cursor_position().X + short(caption_font_size), start_cord.Y }; //+ short(caption_font_size) };

    // Selected caption
    console_handler::console_utils::set_console_cursor_pos({ start_cord.X, start_cord.Y + short(3 * caption_font_size) });
    console_handler::ascii_block_list selected_caption = console_handler::ascii_block_list(caption_color_ + "Selected:", caption_font_size);
    selected_caption.draw();

    // Remember selected position
    selected_cursor_pos_ = console_handler::console_utils::get_console_cursor_position();
    selected_cursor_pos_ = { selected_cursor_pos_.X + short(caption_font_size), selected_cursor_pos_.Y - short(caption_font_size) };

    // Write picked and remaining caption
    console_handler::console_utils::set_console_cursor_pos({ start_cord.X, start_cord.Y + short(6 * caption_font_size) });
    console_handler::ascii_block_list picked_caption = console_handler::ascii_block_list(caption_color_ + "Picked:", caption_font_size);
    picked_caption.draw();

    // Remember picked position
    picked_cursor_pos_ = console_handler::console_utils::get_console_cursor_position();
    picked_cursor_pos_ = { picked_cursor_pos_.X + short(caption_font_size), picked_cursor_pos_.Y - short(caption_font_size) };

    console_handler::console_utils::set_console_cursor_pos({ start_cord.X, start_cord.Y + short(7 * caption_font_size) });
    console_handler::ascii_block_list remaining_caption = console_handler::ascii_block_list(caption_color_ + "Remaining:", caption_font_size);
    remaining_caption.draw();

    // Remember remaining position
    remaining_cursor_pos_ = console_handler::console_utils::get_console_cursor_position();
    remaining_cursor_pos_ = { remaining_cursor_pos_.X + short(caption_font_size), remaining_cursor_pos_.Y - short(caption_font_size) };
  }

  void play::draw_current_player(const std::string current_player, const std::string last_player)
  {
    // remove last player name
    console_handler::console_utils::set_console_cursor_pos(current_player_cursor_pos_);
    console_handler::ascii_block_list text_ascii_last = console_handler::ascii_block_list(background_color_ + last_player, font_size_);
    text_ascii_last.draw();

    // write new player name
    console_handler::console_utils::set_console_cursor_pos(current_player_cursor_pos_);
    console_handler::ascii_block_list text_ascii_current = console_handler::ascii_block_list(text_value_color_ + current_player, font_size_);
    text_ascii_current.draw();
  }

  void play::draw_selected(const int selected, const int last_selected)
  {
    // remove last
    console_handler::console_utils::set_console_cursor_pos(selected_cursor_pos_);
    console_handler::ascii_block_list text_last = console_handler::ascii_block_list(background_color_ + std::to_string(last_selected), font_size_);
    text_last.draw();

    // write new
    console_handler::console_utils::set_console_cursor_pos(selected_cursor_pos_);
    console_handler::ascii_block_list text_current = console_handler::ascii_block_list(text_value_color_ + std::to_string(selected), font_size_);
    text_current.draw();
  }

  void play::draw_remaining(const int remaining, const int last_remaining)
  {
    // remove last
    console_handler::console_utils::set_console_cursor_pos(remaining_cursor_pos_);
    console_handler::ascii_block_list text_last = console_handler::ascii_block_list(background_color_ + std::to_string(last_remaining), font_size_);
    text_last.draw();

    // write new
    console_handler::console_utils::set_console_cursor_pos(remaining_cursor_pos_);
    console_handler::ascii_block_list text_current = console_handler::ascii_block_list(text_value_color_ + std::to_string(remaining), font_size_);
    text_current.draw();
  }

  void play::draw_picked(const int picked, const int last_picked)
  {
    // remove last
    console_handler::console_utils::set_console_cursor_pos(picked_cursor_pos_);
    console_handler::ascii_block_list text_last = console_handler::ascii_block_list(background_color_ + std::to_string(last_picked), font_size_);
    text_last.draw();

    // write new
    console_handler::console_utils::set_console_cursor_pos(picked_cursor_pos_);
    console_handler::ascii_block_list text_current = console_handler::ascii_block_list(text_value_color_ + std::to_string(picked), font_size_);
    text_current.draw();
  }

  void play::win_screen()
  {
    console_handler::console_output::fill_background(background_color_);

    std::vector<console_handler::grid_item> new_game_main_menu_items;

    // Change names
    new_game_main_menu_items.push_back(console_handler::grid_item([](bool selected) { new_game(); }, "{#FFFFFF}New Game", "{_#66BB6A}",
      "../Icons/Play.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 5));

    // Main Menu
    new_game_main_menu_items.push_back(console_handler::grid_item([](bool selected) { main::draw(); }, "{#FFFFFF}Main Menu", "{_#757575}",
      "../Icons/Home.bmp", "{#FFFFFF}", ' ', "{_#03b7a5}", 5));

    // Draw question grid
    console_handler::dynamic_grid change_name_question =
      console_handler::dynamic_grid("Player > " + (player_a_is_ ? options::name_player_a : options::name_player_b) + " < won!", 20, new_game_main_menu_items, 10, 5);
    change_name_question.set_size_multiplicator(0.5);
    change_name_question.recalculate_item_size();
    change_name_question.draw();
    change_name_question.select();
  }
}
