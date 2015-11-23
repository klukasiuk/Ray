#pragma once

#include <fstream>
#include <string>
#include <GLFW/glfw3.h>

using std::string;

// Pisze logi 
class Logger
{
  private :

  std::ofstream log;                         //Strumieñ zapisu

  public :

  Logger(string logname);                    // Konstruktor 
  ~Logger();                                 // Destruktor

  void operator << (string msg);
  void operator << (int code);
  void operator << (const char * msg);

  void msg(string msg, int code);
};