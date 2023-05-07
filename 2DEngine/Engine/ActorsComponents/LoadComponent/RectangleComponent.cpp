#include "RectangleComponent.h"

RectangleComponent::RectangleComponent(Actor* ownerP, Rectangle rectP, Color colorP, int drawOrderP) : LoadComponent(ownerP, drawOrderP), rect(rectP), color(colorP)
{
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::setRect(const Rectangle rectP)
{
	rect = rectP;
}

void RectangleComponent::setColor(const Color colorP)
{
	color = colorP;
}

void RectangleComponent::draw(RendererSDL& renderer)
{
	if (willLoad)
	{
		renderer.drawRect(owner, rect, color);
	}
}