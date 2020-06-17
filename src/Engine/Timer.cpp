#include "Timer.h"

Timer::Timer()
{
	//Initialise
	StartTicks = 0;
	PausedTicks = 0;
	bPaused = false;
	bStarted = false;
}

void Timer::Start()
{
	bStarted = true;
	bPaused = false;

	StartTicks = SDL_GetTicks();
	PausedTicks = 0;
}

void Timer::Stop()
{
	bStarted = false;
	bPaused = false;
	StartTicks = 0;
	PausedTicks = 0;
}

void Timer::Pause()
{
	if(bStarted && !bPaused)
	{
		bPaused = true;
		PausedTicks = SDL_GetTicks() - StartTicks;
		StartTicks = 0;
	}
}

void Timer::Resume()
{
	if( bStarted && bPaused )
	{
		bPaused = false;
		StartTicks = SDL_GetTicks() - PausedTicks;
		PausedTicks = 0;
	}
}

void Timer::Reset()
{
	StartTicks = 0;
	PausedTicks = 0;
	bPaused = false;
	bStarted = true;

	StartTicks = SDL_GetTicks();
	PausedTicks = 0;
}

Uint32 Timer::GetTicks()
{
	if(bStarted)
	{
		if(bPaused)
		{
			return PausedTicks;
		}
		else
		{
			return SDL_GetTicks() - StartTicks;
		}
	}
	return 0;
}

bool Timer::IsStarted()
{
	return bStarted;
}
bool Timer::IsActive()
{
	return bStarted && !bPaused;
}
bool Timer::IsPaused()
{
	return bStarted && bPaused;
}

