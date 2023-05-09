#pragma once
#include "LoadGridTile.h"
#include <Engine/Utilitaire/Color.h>

class LoadGridTileRectangle : public LoadGridTile
{

public:

	LoadGridTileRectangle(Color colorP, Rectangle proportionP);
	LoadGridTileRectangle() = delete;
	virtual ~LoadGridTileRectangle();

	void draw(RendererSDL& renderer, Rectangle tile, int traductionIndex) override;

private:

	Color color;
	Rectangle proportion{ Rectangle::unitRect };
	bool proportionCorrect{ false };
};

