#pragma once
#include "Paddle.h"
#include <Engine/ActorsComponents/ControlsComponents/MouseComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/BorderLimitComponent.h>

class PlayerPaddle : public Paddle
{

public:

	PlayerPaddle();
	PlayerPaddle(const PlayerPaddle&) = delete;
	PlayerPaddle& operator=(const PlayerPaddle&) = delete;

private:

	MouseComponent* mouseComp;
	BorderLimitComponent* borderLimitInterComp;
};

