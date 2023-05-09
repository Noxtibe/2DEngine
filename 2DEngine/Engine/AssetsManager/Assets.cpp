#include "Assets.h"
#include "../Utilitaire/Log.h"
#include <fstream>
#include <iostream>

map<string, Texture> Assets::textures;
map<string, Font*> Assets::fonts;
map<string, GridMap*> Assets::gridMaps;
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

GridMap* Assets::loadGridMap(const string& filename, const string& name)
{
	gridMaps[name] = loadGridMapFromFile((assetsPath + filename).c_str());
	return gridMaps[name];
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

GridMap* Assets::getGridMap(const string& name)
{
	if (gridMaps.find(name) == end(gridMaps) || gridMaps[name] == nullptr)
	{
		Log::error(LogCategory::Application, "GridMap Map " + name + " does not exist in assets manager.");
	}
	return gridMaps[name];
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

GridMap* Assets::loadGridMapFromFile(const string& filePath)
{
	GridMap GridMap_map;
	return GridMap_map.load(filePath);
}