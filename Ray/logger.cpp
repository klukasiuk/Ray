#include "logger.h"

#include <iostream>


// Konstruktor
Logger::Logger(string logname)
{
  logname = logname + ".txt";
  log.open(logname.c_str());                                      // Otwiera plik log.txt do zapisu 

  log.precision(5);
}

//Destruktor
Logger::~Logger()
{
  log.close();                                                    // Zamyka strumie� danych
}

// Zapisuje wiadomo��
void Logger::operator<<(string message)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<message<<"\n";                 // zapisuje czas i wiadomo��
	 
	log.flush();                                                  // czy�ci strumie�
} 

// Zapisuje wiadomo�� z parametrem 
void Logger::operator<<(int var)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<var<<"\n\n";                     // zapisuje czas i parametr

	log.flush();                                                  // czy�ci strumie�
}


// Zapisuje wiadomo�� z parametrem 
void Logger::operator<<(const char * msg)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<msg<<"\n";                     // zapisuje czas i wiadomo��

	log.flush();                                                  // czy�ci strumie�
}


void Logger::msg(string msg , int code)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<msg<<" : "<<code<<"\n";                     // zapisuje czas i wiadomo��

	log.flush();                                                  // czy�ci strumie�
}