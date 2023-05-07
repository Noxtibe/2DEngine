#pragma once
#include <SDL.h>

class Window
{
public:
	Window() = default;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool initialize(const char* windowName, int width, int height);
	void close();

	SDL_Window* getSDLWindow() const { return SDLWindow; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Window* SDLWindow{ nullptr };
	int width{ 0 };
	int height{ 0 };
};

