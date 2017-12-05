#pragma once
#include "console_handler.h"
namespace console_handler
{
  /**
   * \brief Contains the avalible console_types
   * \attention Please update the function console_utils::get_console_type_text
   */
  enum CONSOLE_HANDLER_API console_type
  {
    menu,
    info
  };
}
