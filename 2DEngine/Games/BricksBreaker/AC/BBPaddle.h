#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <LoadComponent/RectangleComponent.h>
#include <CollisionComponents/RectangleCollisionComponent.h>
#include <ControlsComponents/MouseComponent.h>
#include <CollisionComponents/BorderLimitComponent.h>

class BBPaddle : public Actor
{

public:

	BBPaddle();
	BBPaddle(const BBPaddle&) = delete;
	BBPaddle& operator=(const BBPaddle&) = delete;

	RectangleCollisionComponent* GetCol() { return rectColComp; }
	void SetLoadValue(bool value);

private:

	RectangleComponent* drawRectComp;
	RectangleCollisionComponent* rectColComp;
	MouseComponent* mouseMoveComp;
	BorderLimitComponent* borderLimitInterComp;
};

