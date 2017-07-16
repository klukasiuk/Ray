#pragma once
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
//#include <Windows.h>


// Prosty timer
class Timer
{

 private :

	// Aktualny Czas
	double World_Time;

	// Czas w³¹czenia
	double Start_Time;

	// Liczba akutalizacji ( klatek)
	int updates;

	// Czy dzia³a
    bool running;

public :

	Timer(void);           // Konstruktor

	void   Start();      
	void   Stop();
	void   Reset();

	double GetTime();     // Zwraca naliczony czas ( milisekundy)
	int    GetUpdates();  // Zwraca iloœæ uaktualnieñ

	void   Update();      // Uaktualnia zmienne
};



// Narzêdzie do regulowania frame rate i liczenia fps
class FPS
{
  
 public :

	// Aktualny Czas
	double World_Time;

	// Czas od w³¹czenia
	double Start_Time;

	// Czas od ostaniej aktualizacji
	double Delta_Time;

	// Liczba akutalizacji ( klatek)
	int updates;

	// Liczba klatek na sekundê
    float rate;

	//Co ile klatek liczy FPS
	int frames;

	// Wartoœæ blokady klatek
	int max ;

public :

	FPS(void);                       // Konstruktor

	void Update();                   // Uaktualnia zmienne

	void Block(int maximum);         // Ustawia blokowanie FPS

	void Free();                     // Zwalnie blokowanie

	void Set_Frames(int fr);         // Zmienie co ile klatek jest liczony FPS (standardowo 100)

	double Delta();                  // Zwraca delte czasu w milisekundach
};


void SleepFor(int miliseconds);