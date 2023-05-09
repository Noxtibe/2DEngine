#include "BricksBreakerGame.h"
#include <Engine/AssetsManager/Assets.h>
#include <Engine/Game.h>
#include "AC/BBBall.h"
#include "AC/BBPaddle.h"
#include "AC/BBManager.h"
#include "AC/BBGrid.h"

void BricksBreakerGame::load(Game* game)
{
	Assets::setAssetsPath("Games/BrickBreaker/Assets/");


	auto ball = new BBBall();

	auto paddle = new BBPaddle();
	paddle->setPosition(Vector2{ 400.0f, 500.0f });

	auto grid = new BBGrid(10, 11, Vector2{ 80.0f, 20.0f }, Color::red);
	grid->setPosition(Vector2{ 0.0f, 60.0f });

	auto manager = new BBManager(ball, paddle, grid);


	game->getCamera().setCamPos(Vector2{ 0.0f, 0.0f });
}