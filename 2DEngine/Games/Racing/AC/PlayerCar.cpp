#include "PlayerCar.h"
#include <Engine/Maths/Maths.h>
#include <Engine/ActorsComponents/GridComponent/GridComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/RectangleCollisionComponent.h>

PlayerCar::PlayerCar(Texture& carTextureP, bool moveWithArrows) : Actor()
{
	SpriteComp = new SpriteComponent(this, carTextureP, Vector2{ -10.0f, -5.0f }, RendererSDL::Flip::Horizontal);

	circleColComp = new CircleCollisionComponent(this);
	circleColComp->setRadius(10.0f);

	moveComp = new RotationComponent(this, Maths::pi * 0.5f);

	if (moveWithArrows)
	{
		moveComp->setForwardKey(SDL_SCANCODE_UP);
		moveComp->setBackKey(SDL_SCANCODE_DOWN);
		moveComp->setRightKey(SDL_SCANCODE_RIGHT);
		moveComp->setLeftKey(SDL_SCANCODE_LEFT);
	}
	else
	{
		moveComp->setForwardKey(SDL_SCANCODE_W);
		moveComp->setBackKey(SDL_SCANCODE_S);
		moveComp->setRightKey(SDL_SCANCODE_D);
		moveComp->setLeftKey(SDL_SCANCODE_A);
	}

	borderLimitInterComp = new BorderLimitComponent(this, moveComp, circleColComp);
	borderLimitInterComp->setInteractions(BorderLimitInteractions::Block, BorderLimitInteractions::Block, BorderLimitInteractions::Block, BorderLimitInteractions::Block);
	borderLimitInterComp->autoUpdate = true;
}

void PlayerCar::TestGridCol(GridComponent& grid)
{
	if (grid.intersectWithCircleCol(*circleColComp))
	{
		moveComp->rewindLastMovement(true, true);
		moveComp->setSpeed(moveComp->getSpeed() * -0.3f);
	}
}

bool PlayerCar::TestFinishLineTrigger(RectangleCollisionComponent& finishLine)
{
	return finishLine.intersectWithCircleCollision(*circleColComp);
}

void PlayerCar::Reset(Vector2 position, float rotation)
{
	moveComp->setSpeed(0.0f);
	moveComp->setArbitraryAngle(rotation);
	setPosition(position);
}

void PlayerCar::SetLoadValue(bool draw)
{
	SpriteComp->setWillLoad(draw);
}
