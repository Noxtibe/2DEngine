#include "Timer.h"
#include <SDL_timer.h>
#include <algorithm>

unsigned int Timer::computeDeltaTime()
{
	frameStart = SDL_GetTicks();
	Uint32 dt = frameStart - lastFrame;
	lastFrame = frameStart;
	return std::min(dt, MAX_DT);    // Clamp delta time
}

void Timer::delayTime()
{
	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < FRAME_DELAY)
	{
		SDL_Delay(FRAME_DELAY - frameTime);
	}
}