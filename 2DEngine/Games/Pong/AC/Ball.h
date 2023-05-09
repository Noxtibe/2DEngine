#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/LoadComponent/CircleComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/CircleCollisionComponent.h>
#include <Engine/ActorsComponents/ControlsComponents/VelocityComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/BorderLimitComponent.h>

class GameManager;

class Ball : public Actor
{

public:

	Ball();
	Ball(const Ball&) = delete;
	Ball& operator=(const Ball&) = delete;

	void updateActor(float dt) override;
	void TestCollision(class RectangleCollisionComponent* col, bool testAtRight);

	void SetManager(GameManager* gameManagerP);
	void ResetPos();
	void ReverseXMovement();
	void SetRandomYVelocity();
	void SetDirectedYMovement(Rectangle colRect);
	void PauseMovement();
	void ResumeMovement();
	void SetLoadValue(bool value);

	void SetSpeed(float speedP);
	float GetSpeed() const { return speed; }

private:

	GameManager* gameManager{ nullptr };

	CircleComponent* circleComp;
	CircleCollisionComponent* circleColComp;
	VelocityComponent* moveComp;
	BorderLimitComponent* borderLimitInterComp;

	float baseSpeed{ 300.0f };
	float speed{ 0.0f };
	float directMultiplier{ 1.5f };
	float speedBoost{ 15.0f };
};

