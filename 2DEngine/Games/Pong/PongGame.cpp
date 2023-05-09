#include "PongGame.h"
#include <Engine/AssetsManager/Assets.h>
#include <Engine/Game.h>
#include "AC/Ball.h"
#include "AC/PlayerPaddle.h"
#include "AC/IAPaddle.h"
#include "AC/GameManager.h"


void PongGame::load(Game* game)
{
	Assets::setAssetsPath("Games/Pong/Assets/");

	Assets::loadFont("Pixeled.ttf", "pixeled30", 30);

	auto ball = new Ball();

	auto left_paddle = new PlayerPaddle();
	left_paddle->setPosition(Vector2{ 10.0f, 300.0f });

	auto right_paddle = new IAPaddle(Vector2{ game->getScreenWidth() - 20.0f, 300.0f });

	auto manager = new GameManager(ball, left_paddle, right_paddle, Assets::getFont("pixeled30"));


	game->getCamera().setCamPos(Vector2{ 0.0f, 0.0f });
}