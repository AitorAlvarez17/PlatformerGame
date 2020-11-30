// ----------------------------------------------------
// Slow timer with microsecond precision
// ----------------------------------------------------

#include "PerfTimer.h"
#include "SDL\include\SDL_timer.h"

uint64 PerfTimer::frequency = 0;

// L07: DONE 2: Fill Constructor, Start(),ReadMs() and ReadTicks() methods
// they are simple, one line each!

PerfTimer::PerfTimer()
{
	//...
	frequency = SDL_GetPerformanceFrequency();
	Start();
}

void PerfTimer::Start()
{
	//...
	startTime = SDL_GetPerformanceCounter();
}

double PerfTimer::ReadMs() const
{
	
	return 1000.0 * ((static_cast<double>(SDL_GetPerformanceCounter()) - startTime) / (frequency));;
}

uint64 PerfTimer::ReadTicks() const
{

	return SDL_GetPerformanceFrequency() - startTime;
}
