#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/GridComponent/GridComponent.h>

class RTSMap : public Actor
{

public:

	RTSMap(GridMap* gridMapP);
	RTSMap() = delete;
	RTSMap(const RTSMap&) = delete;
	RTSMap& operator=(const RTSMap&) = delete;

	GridComponent& GetGridComp() { return *gridComp; }

private:

	GridComponent* gridComp;
};

