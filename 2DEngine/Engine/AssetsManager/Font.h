#pragma once
#include <string>
#include <SDL_ttf.h>

using std::string;

class Font
{

public:

	Font(string pathP, TTF_Font* sdlFontP, int sizeP);
	Font() = default;
	static Font* load(const string& pathP, int sizeP);

	string getPath() const { return path; }
	int getSize() const { return size; }
	TTF_Font* getSdlFont() const { return sdlFont; }

private:

	string path{ "" };
	int size{ 0 };
	TTF_Font* sdlFont{ nullptr };
};