#include "GridTileSprite.h"

GridTileSprite::GridTileSprite(Texture& textureP) : LoadGridTile(), texture(textureP)
{
}

GridTileSprite::~GridTileSprite()
{
}

void GridTileSprite::draw(RendererSDL& renderer, Rectangle tile, int traductionIndex)
{
	renderer.drawTileSprite(tile, texture, Rectangle::nullRect, Vector2::zero, RendererSDL::Flip::None);
}
