#pragma once
#ifdef CONSOLE_HANDLER_EXPORTS
#define CONSOLE_HANDLER_API __declspec(dllexport)
#else
#define CONSOLE_HANDLER_API __declspec(dllimport)
#endif // CONSOLE_HANDLER_EXPORTS

namespace console_handler
{
  class console_handler_core
  {
  public:
    static CONSOLE_HANDLER_API void prepare_console();
  };
}
