#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include "RCTrack.h"
#include "PlayerCar.h"
#include <Engine/ActorsComponents/CollisionComponents/RectangleCollisionComponent.h>
#include <Engine/ActorsComponents/LoadComponent/TextComponent.h>

class RCManager : public Actor
{

public:

	RCManager(RCTrack* trackP, PlayerCar* playerOneCarP, PlayerCar* playerTwoCarP);
	RCManager() = delete;
	RCManager(const RCManager&) = delete;
	RCManager& operator=(const RCManager&) = delete;

	void updateActor(float dt) override;

private:

	void PauseGame(bool playerTwoWin);
	void ResumeGame();

	RCTrack* track;
	PlayerCar* playerOneCar;
	PlayerCar* playerTwoCar;

	RectangleCollisionComponent* finishLineTrigger;
	TextComponent* victoryTextComp;
	TextComponent* resetTextComp;

	bool isPaused{ false };
};

