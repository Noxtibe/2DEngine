#pragma once
#include <SDL.h>

struct Color
{
	int r{ 0 };
	int g{ 0 };
	int b{ 0 };
	int a{ 0 };

	static const Color black;
	static const Color white;
	static const Color grey;
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color magenta;
	static const Color yellow;
	static const Color cyan;
	static const Color transparency;

	Color() = default;
	Color(int rP, int gP, int bP, int aP) : r{ rP }, g{ gP }, b{ bP }, a{ aP } {}

	void set(int rP, int gP, int bP, int aP);

	SDL_Color toSDLColor()
	{
		return SDL_Color{ static_cast<uint8_t>(r),
			static_cast<uint8_t>(g),
			static_cast<uint8_t>(b),
			static_cast<uint8_t>(a) };
	}

	static Color HSV(float h, float s, float v);
};

