#include "RCManager.h"
#include <iostream>
#include <Engine/AssetsManager/Assets.h>
#include <Engine/Game.h>

RCManager::RCManager(RCTrack* trackP, PlayerCar* playerOneCarP, PlayerCar* playerTwoCarP) : Actor(), track(trackP), playerOneCar(playerOneCarP), playerTwoCar(playerTwoCarP)
{
	playerOneCar->Reset(track->GetPlayerStartPos(6), Maths::pi * 0.5f);
	playerTwoCar->Reset(track->GetPlayerStartPos(6), Maths::pi * 0.5f);

	finishLineTrigger = new RectangleCollisionComponent(this);
	finishLineTrigger->setRectangle(Rectangle{ 40.0f, 480.0f, 40.0f, 80.0f });

	victoryTextComp = new TextComponent(this, Assets::getFont("pixeled30"), "BLACK CAR WIN !", Color::white,
		Vector2{ getGame().getScreenWidth() / 2.0f, getGame().getScreenHeight() / 15.0f }, true);
	victoryTextComp->setWillLoad(false);
	resetTextComp = new TextComponent(this, Assets::getFont("pixeled30"), "PRESS LEFT CLICK TO RESET", Color::white,
		Vector2{ getGame().getScreenWidth() / 2.0f, getGame().getScreenHeight() / 3.0f }, true);
	resetTextComp->setWillLoad(false);
}

void RCManager::updateActor(float dt)
{
	if (isPaused)
	{
		if (getGame().isKeyPressed(SDL_MOUSE_LEFT_BUTTON))
		{
			ResumeGame();
		}
	}
	else
	{
		playerOneCar->TestGridCol(track->GetGridComp());
		playerTwoCar->TestGridCol(track->GetGridComp());

		if (playerOneCar->TestFinishLineTrigger(*finishLineTrigger))
		{
			PauseGame(false);
		}
		else if (playerTwoCar->TestFinishLineTrigger(*finishLineTrigger))
		{
			PauseGame(true);
		}
	}
}

void RCManager::PauseGame(bool playerTwoWin)
{
	isPaused = true;

	playerOneCar->SetLoadValue(false);
	playerTwoCar->SetLoadValue(false);

	victoryTextComp->setText(playerTwoWin ? "GREEN CAR WIN !" : "RED CAR WIN !");
	victoryTextComp->setWillLoad(true);
	resetTextComp->setWillLoad(true);
}

void RCManager::ResumeGame()
{
	victoryTextComp->setWillLoad(false);
	resetTextComp->setWillLoad(false);

	track->ResetTrack();
	playerOneCar->Reset(track->GetPlayerStartPos(6), Maths::pi * 0.5f);
	playerTwoCar->Reset(track->GetPlayerStartPos(6), Maths::pi * 0.5f);
	playerOneCar->SetLoadValue(true);
	playerTwoCar->SetLoadValue(true);

	isPaused = false;
}
