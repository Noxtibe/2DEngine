#pragma once
#include "ITurn.h"
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/LoadComponent/SpriteComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/RectangleCollisionComponent.h>
#include <Engine/ActorsComponents/ControlsComponents/DestinationComponent.h>
#include <vector>

class RTSPlayerTurn : public ITurn, public Actor
{

public:

	RTSPlayerTurn(Texture& playerTextureP);
	RTSPlayerTurn() = delete;
	RTSPlayerTurn(const RTSPlayerTurn&) = delete;
	RTSPlayerTurn& operator=(const RTSPlayerTurn&) = delete;

	void TurnAction() override;
	bool IsUnderMouse(Vector2 mousePos) const;
	bool MovingBetweenTiles() const;

	void SetMovementList(std::vector<Vector2> movementListP);
	void ForceClearMovement();
	bool HasMovementWaiting() const;

private:

	SpriteComponent* spriteComp;
	RectangleCollisionComponent* rectColComp;
	DestinationComponent* moveComp;
	std::vector<Vector2> movementList;
};

