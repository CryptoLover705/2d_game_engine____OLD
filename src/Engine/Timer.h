#pragma once
#include "SDL2/SDL.h"

class Timer
{
public:
	Timer();

	// Actions
	virtual void Start();
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();
	virtual void Reset();
	Uint32 GetTicks();

	bool IsStarted();
	bool IsActive();
	bool IsPaused();

private:
	Uint32 StartTicks, PausedTicks;
	bool bPaused, bStarted;
};
