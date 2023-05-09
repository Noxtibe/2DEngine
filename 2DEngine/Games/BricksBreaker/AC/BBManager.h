#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include "BBBall.h"
#include "BBPaddle.h"
#include "BBGrid.h"

class BBManager : public Actor
{

public:

	BBManager(BBBall* ballP, BBPaddle* paddleP, BBGrid* gridP);
	BBManager() = delete;
	BBManager(const BBManager&) = delete;
	BBManager& operator=(const BBManager&) = delete;

	void updateActor(float dt) override;

private:

	BBBall* ball;
	BBPaddle* paddle;
	BBGrid* grid;

	int numberOfBricks;

	void ResetGrid();
};

