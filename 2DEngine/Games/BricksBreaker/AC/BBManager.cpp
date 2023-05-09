#include "BBManager.h"
#include <Engine/Game.h>

BBManager::BBManager(BBBall* ballP, BBPaddle* paddleP, BBGrid* gridP) : Actor(), ball(ballP), paddle(paddleP), grid(gridP)
{
	ResetGrid();
}

void BBManager::updateActor(float dt)
{
	if (ball->UpdateBall())
	{
		ball->ResetPos();
		ResetGrid();
	}

	if (ball->TestPaddleCollision(paddle->GetCol()) && numberOfBricks <= 0)
	{
		ResetGrid();
	}

	Vector2 ball_screen_pos = ball->getPosition() - getGame().getCamera().getCamPos();
	int grid_intersect_x, grid_intersect_y;
	if (grid->GetGrid()->intersectWithScreenPoint(ball_screen_pos, &grid_intersect_x, &grid_intersect_y))
	{
		grid->GetGrid()->setGridElement(grid_intersect_x, grid_intersect_y, 0);
		numberOfBricks--;


		Vector2 previous_ball_screen_pos = ball->GetPreviousPos() - getGame().getCamera().getCamPos();
		int previous_grid_intersect_x, previous_grid_intersect_y;
		grid->GetGrid()->intersectWithScreenPoint(previous_ball_screen_pos, &previous_grid_intersect_x, &previous_grid_intersect_y);

		bool both_tests_failed = true;

		if (grid_intersect_x != previous_grid_intersect_x) //  should come from horizontal
		{
			if (!grid->GetGrid()->intersectWithScreenPoint(Vector2{ previous_ball_screen_pos.x, ball_screen_pos.y })) //  the horizontal side of the brick we destroyed isn't blocked
			{
				ball->ReverseXMovement();
				both_tests_failed = false;
			}
		}

		if (grid_intersect_y != previous_grid_intersect_y) //  should come from vertical (can be in both)
		{
			if (!grid->GetGrid()->intersectWithScreenPoint(Vector2{ ball_screen_pos.x, previous_ball_screen_pos.y })) //  the vertical side of the brick we destroyed isn't blocked
			{
				ball->ReverseYMovement();
				both_tests_failed = false;
			}
		}

		if (both_tests_failed) //  the ball hit a closed corner and only touched the inner tile of the corner so both tests have failed
		{
			ball->ReverseXMovement();
			ball->ReverseYMovement();
		}
	}
}

void BBManager::ResetGrid()
{
	grid->ResetGrid();
	numberOfBricks = grid->GetGrid()->getGridWidth() * grid->GetGrid()->getGridHeight();
}
