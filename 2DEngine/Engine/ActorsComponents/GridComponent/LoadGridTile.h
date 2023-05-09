#pragma once
#include <Engine/RendererSDL.h>
#include <Engine/Maths/Rectangle.h>

class LoadGridTile
{

public:

	LoadGridTile();
	virtual ~LoadGridTile();

	virtual void draw(RendererSDL& renderer, Rectangle tile, int traductionIndex);
};

