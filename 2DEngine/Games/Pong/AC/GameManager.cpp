#include "GameManager.h"
#include <Engine/Game.h>

GameManager::GameManager(Ball* ballP, PlayerPaddle* leftPaddleP, IAPaddle* rightPaddleP, Font* fontP) : Actor(), ball(ballP), leftPaddle(leftPaddleP), rightPaddle(rightPaddleP), font(fontP)
{
	leftLoadTextComp = new TextComponent(this, font, "0",
		Color::white, Vector2{ 100.0f, 0.0f }, true, 1000);

	rightLoadTextComp = new TextComponent(this, font, "0",
		Color::white, Vector2{ 700.0f, 0.0f }, true, 1000);

	victoryLoadTextComp = new TextComponent(this, font, "PONG",
		Color::white, Vector2{ 400.0f, 180.0f }, true, 1000);

	resetLoadTextComp = new TextComponent(this, font, "PRESS LEFT CLICK TO PLAY",
		Color::white, Vector2{ 400.0f, 330.0f }, true, 1000);


	for (int i = 0; i < 15; i++)
	{
		lineLoadRectComps[i] = new RectangleComponent(this, Rectangle{ 399.0f, i * 40.0f, 2.0f, 20.0f }, Color::white, 10);
		lineLoadRectComps[i]->setWillLoad(false);
	}

	ball->SetManager(this);
	ball->PauseMovement();
	ball->SetLoadValue(false);
	leftPaddle->SetLoadValue(false);
	rightPaddle->SetLoadValue(false);
}

void GameManager::updateActor(float dt)
{
	if (!isGamePaused)
	{
		ball->TestCollision(leftPaddle->GetCol(), false);
		ball->TestCollision(rightPaddle->GetCol(), true);

		rightPaddle->UpdateVelocity(ball->getPosition().y);
	}
	else
	{
		if (getGame().isKeyPressed(SDL_MOUSE_LEFT_BUTTON))
		{
			ResumeGame();
			ResetScores();
		}
	}
}

void GameManager::ScoreAtLeft()
{
	scoreRight++;
	if (scoreRight >= maxScore)
	{
		ball->ResetPos();
		rightLoadTextComp->setText(std::to_string(scoreRight));
		victoryLoadTextComp->setText("RIGHT PLAYER WINS !");
		PauseGame();
	}
	else
	{
		ball->ResetPos();
		rightLoadTextComp->setText(std::to_string(scoreRight));
		rightPaddle->ResetPos();
	}
}

void GameManager::ScoreAtRight()
{
	scoreLeft++;
	if (scoreLeft >= maxScore)
	{
		ball->ResetPos();
		leftLoadTextComp->setText(std::to_string(scoreLeft));
		victoryLoadTextComp->setText("LEFT PLAYER WINS !");
		PauseGame();
	}
	else
	{
		ball->ResetPos();
		leftLoadTextComp->setText(std::to_string(scoreLeft));
		rightPaddle->ResetPos();
	}
}

void GameManager::ResetScores()
{
	scoreLeft = 0;
	scoreRight = 0;
	leftLoadTextComp->setText(std::to_string(scoreLeft));
	rightLoadTextComp->setText(std::to_string(scoreRight));
}

void GameManager::PauseGame()
{
	isGamePaused = true;
	ball->PauseMovement();
	ball->SetLoadValue(false);
	leftPaddle->SetLoadValue(false);
	rightPaddle->SetLoadValue(false);
	victoryLoadTextComp->setWillLoad(true);
	resetLoadTextComp->setWillLoad(true);
	for (int i = 0; i < 15; i++)
	{
		lineLoadRectComps[i]->setWillLoad(false);
	}
}

void GameManager::ResumeGame()
{
	isGamePaused = false;
	ball->ResumeMovement();
	ball->SetLoadValue(true);
	leftPaddle->SetLoadValue(true);
	rightPaddle->SetLoadValue(true);
	victoryLoadTextComp->setWillLoad(false);
	resetLoadTextComp->setWillLoad(false);
	for (int i = 0; i < 15; i++)
	{
		lineLoadRectComps[i]->setWillLoad(true);
	}
}
