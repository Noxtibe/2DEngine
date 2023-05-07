#include "Window.h"
#include "Utilitaire/Log.h"

bool Window::initialize(const char* windowName, int widthP, int heightP)
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0)
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL");
		return false;
	}

	width = widthP;
	height = heightP;
	SDLWindow = SDL_CreateWindow(windowName, 100, 100, width, height, 0);
	if (!SDLWindow)
	{
		Log::error(LogCategory::System, "Failed to create window");
		width = 0;
		height = 0;
		return false;
	}
	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}
