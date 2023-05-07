#pragma once
#include <Engine/RendererSDL.h>
#include <Engine/Maths/Vector2.h>


class ICollision
{

public:

	virtual ~ICollision() {}

	virtual bool intersectWithPoint(const Vector2& point) const = 0;
	virtual bool intersectWithCircleCollision(const class CircleCollisionComponent& collision) const = 0;
	virtual bool intersectWithRectCollision(const class RectangleCollisionComponent& collision) const = 0;

	virtual bool intersectWithY(const float y) const = 0;
	virtual bool intersectWithX(const float x) const = 0;

	virtual float nearestYPosOfY(const float y) const = 0;
	virtual float nearestXPosOfX(const float x) const = 0;
};

