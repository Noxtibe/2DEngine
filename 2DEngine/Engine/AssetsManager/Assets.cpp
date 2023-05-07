#include "Assets.h"
#include "../Utilitaire/Log.h"
#include <fstream>
#include <iostream>

map<string, Texture> Assets::textures;
map<string, Font*> Assets::fonts;
map<string, Grid*> Assets::Grids;
string Assets::assetsPath{ "" };

void Assets::setAssetsPath(const string& path)
{
	assetsPath = path;
}

Texture Assets::loadTexture(RendererSDL& renderer, const string& filename, const string& name)
{
	textures[name] = loadTextureFromFile(renderer, (assetsPath + filename).c_str());
	return textures[name];
}

Font* Assets::loadFont(const string& filename, const string& name, int size)
{
	fonts[name] = loadFontFromFile((assetsPath + filename).c_str(), size);
	return fonts[name];
}

Grid* Assets::loadGrid(const string& filename, const string& name)
{
	Grids[name] = loadGridFromFile((assetsPath + filename).c_str());
	return Grids[name];
}

Texture& Assets::getTexture(const string& name)
{
	if (textures.find(name) == end(textures))
	{
		Log::error(LogCategory::Application, "Texture " + name + " does not exist in assets manager.");
	}
	return textures[name];
}

Font* Assets::getFont(const string& name)
{
	if (fonts.find(name) == end(fonts))
	{
		Log::error(LogCategory::Application, "Font " + name + " does not exist in assets manager.");
	}
	return fonts[name];
}

Grid* Assets::getGrid(const string& name)
{
	if (Grids.find(name) == end(Grids) || Grids[name] == nullptr)
	{
		Log::error(LogCategory::Application, "Grid Map " + name + " does not exist in assets manager.");
	}
	return Grids[name];
}

void Assets::clear()
{
	for (auto iter : textures)
	{
		iter.second.unload();
	}
	textures.clear();

	fonts.clear();
}

Texture Assets::loadTextureFromFile(RendererSDL& renderer, const string& filePath)
{
	Texture texture;
	texture.loadSDL(renderer, filePath);
	return texture;
}

Font* Assets::loadFontFromFile(const string& filePath, int size)
{
	Font font;
	return font.load(filePath, size);
}

Grid* Assets::loadGridFromFile(const string& filePath)
{
	Grid grid_map;
	return grid_map.load(filePath);
}