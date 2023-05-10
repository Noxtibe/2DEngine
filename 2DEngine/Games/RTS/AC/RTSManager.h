#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include "ITurn.h"
#include <vector>

using std::vector;

class RTSManager : public Actor
{

public:

	RTSManager();
	RTSManager(const RTSManager&) = delete;
	RTSManager& operator=(const RTSManager&) = delete;

	void updateActor(float dt) override;

	void AddTurnBasedActor(ITurn* actor);
	void RemoveTurnBasedActor(ITurn* actor);

	void PlayGlobalTurnAction();
	void ForceGlobalTurnAction();

private:

	vector<ITurn*> turnBasedActors;

	float turnMinTime{ 0.05f };
	float turnTimeCounter{ 0.0f };
};

