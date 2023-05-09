#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/GridComponent/GridComponent.h>

class BBGrid : public Actor
{

public:

	BBGrid(int gridSizeX, int gridSizeY, Vector2 tileSize, Color tileColor);
	BBGrid() = delete;
	BBGrid(const BBGrid&) = delete;
	BBGrid& operator=(const BBGrid&) = delete;

	void ResetGrid();

	GridComponent* GetGrid() { return gridComp; }

private:

	GridComponent* gridComp;
};

