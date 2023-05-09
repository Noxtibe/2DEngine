#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/GridComponent/GridComponent.h>

class RCTrack : public Actor
{

public:

	RCTrack(GridMap* gridMapP);
	RCTrack() = delete;
	RCTrack(const RCTrack&) = delete;
	RCTrack& operator=(const RCTrack&) = delete;

	void ResetTrack();
	Vector2 GetPlayerStartPos(int startPosGridIndex);
	GridComponent& GetGridComp() { return *gridComp; }

private:

	GridComponent* gridComp;
	GridMap* gridMap;
};

