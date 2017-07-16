#include "timer.h"

Timer::Timer(void)
{
  running = false;    // Resetuje wszystkie zmienne
  World_Time = 0;
  Start_Time = 0;
  updates=0;
}

void Timer::Start()
{
  running = true;                 // Uruchamia naliczanie

  if(World_Time == 0)             //Jeœli by³ wczeœniej resetowany
  {
  World_Time = Start_Time = glfwGetTime() * 1000;
  }

}

void Timer::Stop()
{
	running = false;              // Zatrzymuje naliczanie
}

void Timer::Reset()
{
  World_Time = 0;                // Wszystko resetuje
  Start_Time = 0;
  updates=0;
}

double Timer::GetTime()
{
	return World_Time - Start_Time;
}

int Timer::GetUpdates()
{
	return updates;
}

void Timer::Update()
{
	if(running)                       
	{
	World_Time = glfwGetTime() * 1000;        // Uaktualnie dane i nalicza uaktualnienia
	updates++;
	}
}

FPS::FPS()
{
  World_Time = 0;
  Start_Time = 0;
  
  updates = 0;

  rate = 0;

  frames = 100;

  max = 0;
};

void FPS::Update()
{
	Delta_Time = World_Time;                  // Pobieramy wczeœniejszy czas

	World_Time = glfwGetTime() * 1000;        // Uaktualnienie czasu

	updates++;                                // Naliczenie aktualizcji

	// Blokada klatek
	if(max > 0)
	{
	  if( World_Time - Start_Time < ( 1000.0f / max ) * updates )            // Jeœli dotychczasowy czas jest mniejszy ni¿ zak³adany 
	  {
		  SleepFor( ( (1000.0f / max) * updates ) - ( World_Time - Start_Time)  );     // Odczekuje ró¿nicê czasów
	  }
	}

	World_Time = glfwGetTime() * 1000;              // Uaktualnia czas po odczekiwaniu ró¿nicy

	Delta_Time = World_Time - Delta_Time;           // Oblicza delte

	if( updates == frames)                          // Sprawdza iloœæ klatek
	{
		rate = ( 1000 * frames ) / ( World_Time - Start_Time);      // Oblicza œredni wynik klatek na sekundê
		World_Time = glfwGetTime() * 1000;                          // Wszystko resetuje
        Start_Time = glfwGetTime() * 1000;
        updates=0;
	}
}

void FPS::Block(int maximum)
{
 max = maximum;
}

void FPS::Free()
{
 max = 0;
}

void FPS::Set_Frames(int fr)
{
 frames=fr;
}

double FPS::Delta()
{
	return Delta_Time;
}

void SleepFor(int miliseconds)
{
	std::chrono::milliseconds dura( miliseconds );
    std::this_thread::sleep_for( dura );
}