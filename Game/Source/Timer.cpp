// ----------------------------------------------------
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL_timer.h"

	
Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	//...
	startTime = SDL_GetTicks();

}

uint32 Timer::Read() const
{
	return SDL_GetTicks() - startTime;
}

float Timer::ReadSec() const
{
	//Est� en ms no secs.
	return float(SDL_GetTicks() - startTime) / 1000.0f;
}