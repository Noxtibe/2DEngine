#include "RTSManager.h"

RTSManager::RTSManager() : Actor()
{
}

void RTSManager::updateActor(float dt)
{
	if (turnTimeCounter > 0.0f)
	{
		turnTimeCounter -= dt;
	}
}

void RTSManager::AddTurnBasedActor(ITurn* actor)
{
	turnBasedActors.emplace_back(actor);
}

void RTSManager::RemoveTurnBasedActor(ITurn* actor)
{
	auto iter = std::find(begin(turnBasedActors), end(turnBasedActors), actor);
	if (iter != end(turnBasedActors))
	{
		std::iter_swap(iter, end(turnBasedActors) - 1);
		turnBasedActors.pop_back();
	}
}

void RTSManager::PlayGlobalTurnAction()
{
	if (turnTimeCounter <= 0.0f)
	{
		ForceGlobalTurnAction();
		turnTimeCounter += turnMinTime;
	}
}

void RTSManager::ForceGlobalTurnAction()
{
	for (auto turn_based_actor : turnBasedActors)
	{
		turn_based_actor->TurnAction();
	}
}