#include "CircleComponent.h"

CircleComponent::CircleComponent(Actor* ownerP, Vector2 offsetP, float radiusP, Color colorP, int drawOrderP) : LoadComponent(ownerP, drawOrderP), offset(offsetP), radius(radiusP), color(colorP)
{
}

CircleComponent::~CircleComponent()
{
}

void CircleComponent::setOffset(const Vector2 offsetP)
{
	offset = offsetP;
}

void CircleComponent::setRadius(const float radiusP)
{
	radius = radiusP;
}

void CircleComponent::setColor(const Color colorP)
{
	color = colorP;
}

void CircleComponent::draw(RendererSDL& renderer)
{
	if (willLoad)
	{
		renderer.drawCircle(owner, offset, radius, color);
	}
}
