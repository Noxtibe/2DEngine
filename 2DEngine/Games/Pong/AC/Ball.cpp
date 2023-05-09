#include "Ball.h"
#include <Engine/Utilitaire/Log.h>
#include <Engine/Utilitaire/Random.h>
#include <Engine/Game.h>
#include <Engine/ActorsComponents/CollisionComponents/RectangleCollisionComponent.h>
#include "GameManager.h"
#include <iostream>

Ball::Ball() : Actor()
{
	circleComp = new CircleComponent(this, Vector2{ 0.0f, 0.0f }, 10.0f, Color::white);

	circleColComp = new CircleCollisionComponent(this);
	circleColComp->setRadius(10.0f);

	moveComp = new VelocityComponent(this);
	moveComp->setVelocity(Vector2{ 1.0f, 0.0f });
	SetRandomYVelocity();

	borderLimitInterComp = new BorderLimitComponent(this, moveComp, circleColComp);
	borderLimitInterComp->setInteractions(BorderLimitInteractions::Bounce, BorderLimitInteractions::Bounce, BorderLimitInteractions::Return, BorderLimitInteractions::Return);

	ResetPos();
	ResumeMovement();
}

void Ball::updateActor(float dt)
{
	int screen_return = borderLimitInterComp->checkBordersInteractions();
	if (screen_return == 3)
	{
		gameManager->ScoreAtLeft();
	}
	else if (screen_return == 4)
	{
		gameManager->ScoreAtRight();
	}
}

void Ball::TestCollision(RectangleCollisionComponent* col, bool testAtRight)
{
	if (col->intersectWithCircleCollision(*circleColComp) && (testAtRight ? moveComp->getVelocity().x > 0.0f : moveComp->getVelocity().x < 0.0f))
	{
		moveComp->rewindLastMovement(true, false);
		ReverseXMovement();
		SetDirectedYMovement(col->getTransformedRectangle());
		speed += speedBoost;
		moveComp->setSpeed(speed);
	}
}

void Ball::SetManager(GameManager* gameManagerP)
{
	gameManager = gameManagerP;
}

void Ball::ResetPos()
{
	speed = baseSpeed;
	moveComp->setSpeed(speed);
	setPosition(Vector2{ getGame().getScreenWidth() / 2.0f, getGame().getScreenHeight() / 2.0f });
	ReverseXMovement();
	SetRandomYVelocity();
}

void Ball::ReverseXMovement()
{
	moveComp->reverseXMovement();
}

void Ball::SetRandomYVelocity()
{
	Vector2 velocity = moveComp->getVelocity();
	float random = Random::getFloatRange(-1.0f, 1.0f);
	moveComp->setVelocity(Vector2{ velocity.x, random });
}

void Ball::SetDirectedYMovement(Rectangle colRect)
{
	float new_velocity_y = (getPosition().y - colRect.y - (colRect.height / 2)) / colRect.height * directMultiplier;
	Vector2 velocity = moveComp->getVelocity();
	moveComp->setVelocity(Vector2{ velocity.x, new_velocity_y });
}

void Ball::PauseMovement()
{
	moveComp->setSpeed(0.0f);
}

void Ball::ResumeMovement()
{
	moveComp->setSpeed(speed);
}

void Ball::SetLoadValue(bool value)
{
	circleComp->setWillLoad(value);
}

void Ball::SetSpeed(float speedP)
{
	speed = speedP;
}
