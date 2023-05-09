#include "GridTileRectangle.h"
#include <Engine/Utilitaire/Log.h>

LoadGridTileRectangle::LoadGridTileRectangle(Color colorP, Rectangle proportionP) : LoadGridTile(), color(colorP), proportion(proportionP)
{
	if (proportion.x >= 0.0f && proportion.x < 1.0f && proportion.y >= 0.0f && proportion.y < 1.0f &&
		proportion.width > 0.0f && proportion.width <= (1.0f - proportion.x) &&
		proportion.height > 0.0f && proportion.height <= (1.0f - proportion.y))
	{
		proportionCorrect = true;
	}
	else
	{
		string msg;
		msg = "The proportion rectangle of a rectangle draw traduction is incorrect.";
		Log::error(LogCategory::Application, msg);
	}
}

LoadGridTileRectangle::~LoadGridTileRectangle()
{
}

void LoadGridTileRectangle::draw(RendererSDL& renderer, Rectangle tile, int traductionIndex)
{
	if (proportionCorrect)
	{
		tile = Rectangle{
			tile.x + proportion.x * tile.width,
			tile.y + proportion.y * tile.height,
			tile.width * proportion.width,
			tile.height * proportion.height
		};
	}

	renderer.drawTileRect(tile, color);
}
