#include "RTSPlayerTurn.h"
#include <Engine/Game.h>

RTSPlayerTurn::RTSPlayerTurn(Texture& playerTextureP) : Actor()
{
	spriteComp = new SpriteComponent(this, playerTextureP, Vector2{ -16.0f, -48.0f }, RendererSDL::Flip::None);

	rectColComp = new RectangleCollisionComponent(this);
	rectColComp->setRectangle(Rectangle{ -16.0f, -16.0f, 32.0f, 32.0f });

	moveComp = new DestinationComponent(this);
	moveComp->setSpeed(200.0f);
}

void RTSPlayerTurn::TurnAction()
{
	if (!movementList.empty())
	{
		Vector2 destination = *(movementList.end() - 1);
		if (destination.x > getPosition().x)
		{
			spriteComp->setFlip(RendererSDL::Flip::None);
		}
		else if (destination.x < getPosition().x)
		{
			spriteComp->setFlip(RendererSDL::Flip::Horizontal);
		}
		moveComp->setDestination(destination);
		movementList.pop_back();
	}
}

bool RTSPlayerTurn::IsUnderMouse(Vector2 mousePos) const
{
	Vector2 reel_mouse_pos = mousePos + getGame().getCamera().getCamPos();

	return rectColComp->intersectWithPoint(reel_mouse_pos);
}

bool RTSPlayerTurn::MovingBetweenTiles() const
{
	return !moveComp->isOnDestination();
}

void RTSPlayerTurn::SetMovementList(std::vector<Vector2> movementListP)
{
	movementList.clear();
	movementList = movementListP;
}

void RTSPlayerTurn::ForceClearMovement()
{
	movementList.clear();
}

bool RTSPlayerTurn::HasMovementWaiting() const
{
	return !movementList.empty() || MovingBetweenTiles();
}
