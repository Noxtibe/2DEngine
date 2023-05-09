#include "BBBall.h"
#include <Engine/ActorsComponents/CollisionComponents/RectangleCollisionComponent.h>

BBBall::BBBall() : Actor()
{
	drawCircleComp = new CircleComponent(this, Vector2{ 0.0f, 0.0f }, 10.0f, Color::white);

	circleColComp = new CircleCollisionComponent(this);
	circleColComp->setRadius(10.0f);

	moveComp = new VelocityComponent(this);

	borderLimitInterComp = new BorderLimitComponent(this, moveComp, circleColComp);
	borderLimitInterComp->setInteractions(BorderLimitInteractions::Bounce, BorderLimitInteractions::Return, BorderLimitInteractions::Bounce, BorderLimitInteractions::Bounce);

	ResetPos();
}

bool BBBall::UpdateBall()
{
	previousPos = moveComp->getBeforeLastMovementPosition();

	int screen_return = borderLimitInterComp->checkBordersInteractions();
	return screen_return == 2;
}

bool BBBall::TestPaddleCollision(RectangleCollisionComponent* col)
{
	bool intersect_with_paddle = col->intersectWithCircleCollision(*circleColComp) && moveComp->getVelocity().y > 0.0f;
	if (intersect_with_paddle)
	{
		moveComp->rewindLastMovement(false, true);
		ReverseYMovement();
		SetDirectedXMovement(col->getTransformedRectangle());
	}
	return intersect_with_paddle;
}

void BBBall::SetManager(BreakerManager* gameManagerP)
{
	gameManager = gameManagerP;
}

void BBBall::ResetPos()
{
	moveComp->setSpeed(speed);
	setPosition(Vector2{ 400.0f, 480.0f });
	moveComp->setVelocity(Vector2{ 0.0f, -1.0f });
}

void BBBall::ReverseXMovement()
{
	moveComp->reverseXMovement();
}

void BBBall::ReverseYMovement()
{
	moveComp->reverseYMovement();
}

void BBBall::SetDirectedXMovement(Rectangle colRect)
{
	float new_velocity_x = (getPosition().x - colRect.x - (colRect.width / 2)) / colRect.width * directMultiplier;
	Vector2 velocity = moveComp->getVelocity();
	moveComp->setVelocity(Vector2{ new_velocity_x, velocity.y });
}

void BBBall::PauseMovement()
{
	moveComp->setSpeed(0.0f);
}

void BBBall::ResumeMovement()
{
	moveComp->setSpeed(speed);
}

void BBBall::SetLoadValue(bool value)
{
	drawCircleComp->setWillLoad(value);
}

void BBBall::SetSpeed(float speedP)
{
	speed = speedP;
}
