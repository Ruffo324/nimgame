#include "stdafx.h"
#include "ConsoleOutput.h"
namespace console_handler
{
  /**
   * \brief 
   * \param message The message wich should be written to the console
   */
  void ConsoleOutput::write(std::string message)
  {
    printf("%s", message.c_str());
  }

 /* ConsoleOutput::ConsoleOutput()
  {

  }


  ConsoleOutput::~ConsoleOutput()
  {

  }*/
}
