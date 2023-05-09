#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/LoadComponent/RectangleComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/RectangleCollisionComponent.h>

class Paddle : public Actor
{

public:

	Paddle();
	Paddle(const Paddle&) = delete;
	Paddle& operator=(const Paddle&) = delete;

	RectangleCollisionComponent* GetCol() { return rectColComp; }
	void SetLoadValue(bool value);

protected:

	RectangleComponent* loadRectComp;
	RectangleCollisionComponent* rectColComp;
};

