#include "error.h"

#include <Windows.h>
#include <string>

using std::to_string;

void Exit()
{
  logger<<"Shutdown";

  release();

  exit(1);
}

void handle_error(int code , const char * msg)
{
  logger.msg(msg , code);

  string error = "ERROR : ";

  error += std::to_string(code);

  MessageBoxA(  NULL ,
	           msg ,
	           error.data() , MB_ICONERROR | MB_OK);
  
  Exit();
}