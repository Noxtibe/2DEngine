#pragma once
#include <Component.h>
#include "ICollision.h"
#include <Engine/Maths/Rectangle.h>
#include <Engine/Maths/Vector2.h>                                                                                                                                          (aled)

class RectangleCollisionComponent : public Component, public ICollision
{

public:

	RectangleCollisionComponent(Actor* ownerP, bool debugEnabledP = true);
	RectangleCollisionComponent() = delete;
	RectangleCollisionComponent(const RectangleCollisionComponent&) = delete;
	RectangleCollisionComponent& operator=(const RectangleCollisionComponent&) = delete;


	Rectangle getRectangle() const { return rectangle; }
	Rectangle getTransformedRectangle() const;
	void setRectangle(Rectangle rectangleP);

	bool intersectWithPoint(const Vector2& point) const override;
	bool intersectWithCircleCollision(const class CircleCollisionComponent& collision) const override;
	bool intersectWithRectCollision(const class RectangleCollisionComponent& collision) const override;

	bool intersectWithY(const float y) const override;
	bool intersectWithX(const float x) const override;

	float nearestYPosOfY(const float y) const override;
	float nearestXPosOfX(const float x) const override;

	void debug(RendererSDL& renderer) override;
	void drawDebug(RendererSDL& renderer, Color debugColor) override;

private:

	Rectangle rectangle{ Rectangle::nullRect };
};