#pragma once
#include "LoadComponent.h"
#include <Engine/Maths/Vector2.h>
#include <Engine/Utilitaire/Color.h>

class CircleComponent : public LoadComponent
{

public:

	CircleComponent(Actor* ownerP, Vector2 offsetP, float radiusP, Color colorP, int drawOrderP = 100);
	virtual ~CircleComponent();
	CircleComponent() = delete;
	CircleComponent(const CircleComponent&) = delete;
	CircleComponent& operator=(const CircleComponent&) = delete;

	virtual void setOffset(const Vector2 offsetP);
	virtual void setRadius(const float radiusP);
	virtual void setColor(const Color colorP);
	virtual void draw(RendererSDL& renderer);

	Vector2 getOffset() const { return offset; }
	float getRadius() const { return radius; }
	Color getColor() const { return color; }

protected:

	Vector2 offset;
	float radius;
	Color color;
};

