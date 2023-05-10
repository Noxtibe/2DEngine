#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include "RTSPlayerTurn.h"
#include <unordered_map>

struct CameraClamp
{
	Vector2 clampMin;
	Vector2 clampMax;
};

class RTSCamera : public Actor
{

public:

	RTSCamera(RTSPlayerTurn* playerP);
	RTSCamera() = delete;
	RTSCamera(const RTSCamera&) = delete;
	RTSCamera& operator=(const RTSCamera&) = delete;

	void updateActor(float dt) override;

private:

	RTSPlayerTurn* player;
	Vector2 halfScreenSize;

	CameraClamp currentClamp;
	std::unordered_map <string, CameraClamp> registeredClamps;
};

