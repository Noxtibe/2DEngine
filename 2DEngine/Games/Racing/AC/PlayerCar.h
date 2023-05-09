#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/LoadComponent/SpriteComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/CircleCollisionComponent.h>
#include <Engine/ActorsComponents/ControlsComponents/RotationComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/BorderLimitComponent.h>

class PlayerCar : public Actor
{

public:

	PlayerCar(Texture& carTextureP, bool moveWithArrows);
	PlayerCar() = delete;
	PlayerCar(const PlayerCar&) = delete;
	PlayerCar& operator=(const PlayerCar&) = delete;

	void TestGridCol(class GridComponent& grid);
	bool TestFinishLineTrigger(class RectangleCollisionComponent& finishLine);

	void Reset(Vector2 position, float rotation);
	void SetLoadValue(bool draw);

private:

	SpriteComponent* SpriteComp;
	CircleCollisionComponent* circleColComp;
	RotationComponent* moveComp;
	BorderLimitComponent* borderLimitInterComp;
};

