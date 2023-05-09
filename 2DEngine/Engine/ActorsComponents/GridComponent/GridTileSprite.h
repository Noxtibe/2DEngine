#pragma once
#include "LoadGridTile.h"
#include <Engine/AssetsManager/Texture.h>

class GridTileSprite : public LoadGridTile
{
public:
	GridTileSprite(Texture& textureP);
	GridTileSprite() = delete;
	virtual ~GridTileSprite();

	void draw(RendererSDL& renderer, Rectangle tile, int traductionIndex) override;

private:
	Texture& texture;
};

