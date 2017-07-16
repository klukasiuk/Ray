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
  log.close();                                                    // Zamyka strumieñ danych
}

// Zapisuje wiadomoœæ
void Logger::operator<<(string message)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<message<<"\n";                 // zapisuje czas i wiadomoœæ
	 
	log.flush();                                                  // czyœci strumieñ
} 

// Zapisuje wiadomoœæ z parametrem 
void Logger::operator<<(int var)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<var<<"\n\n";                     // zapisuje czas i parametr

	log.flush();                                                  // czyœci strumieñ
}


// Zapisuje wiadomoœæ z parametrem 
void Logger::operator<<(const char * msg)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<msg<<"\n";                     // zapisuje czas i wiadomoœæ

	log.flush();                                                  // czyœci strumieñ
}


void Logger::msg(string msg , int code)
{
	log.precision(5);

	log<<glfwGetTime()<<"  -->  "<<msg<<" : "<<code<<"\n";                     // zapisuje czas i wiadomoœæ

	log.flush();                                                  // czyœci strumieñ
}