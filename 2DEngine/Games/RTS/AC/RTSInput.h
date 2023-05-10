#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/GridComponent/GridComponent.h>
#include "RTSPlayerTurn.h"
#include "RTSManager.h"
#include "RTSMap.h"
#include "RTSCamera.h"

class RTSInput : public Actor
{

public:

	RTSInput(RTSManager* managerP, RTSMap* mapP);
	RTSInput(const RTSInput&) = delete;
	RTSInput& operator=(const RTSInput&) = delete;

	void updateActor(float dt) override;

private:

	RTSManager* manager;
	RTSMap* map;

	RTSPlayerTurn* player;
	RTSCamera* camera;

	GridComponent* aimDirGrid;

	Vector2Int lastDestinationRegistered{ Vector2Int::zero };
};

