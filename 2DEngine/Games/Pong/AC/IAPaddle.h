#pragma once
#include "Paddle.h"
#include <Engine/ActorsComponents/ControlsComponents/VelocityComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/BorderLimitComponent.h>

class IAPaddle : public Paddle
{
public:
	IAPaddle(Vector2 startPosP);
	IAPaddle(const IAPaddle&) = delete;
	IAPaddle& operator=(const IAPaddle&) = delete;

	void UpdateVelocity(float ballPosY);
	void ResetPos();

private:
	VelocityComponent* moveComp;
	BorderLimitComponent* screenBorderInterComp;
	Vector2 startPos;
};

