#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ActorsComponents/LoadComponent/CircleComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/CircleCollisionComponent.h>
#include <Engine/ActorsComponents/ControlsComponents/VelocityComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/BorderLimitComponent.h>

class BreakerManager;

class BBBall : public Actor
{

public:

	BBBall();
	BBBall(const BBBall&) = delete;
	BBBall& operator=(const BBBall&) = delete;

	bool TestPaddleCollision(class RectangleCollisionComponent* col);
	bool UpdateBall();

	void SetManager(BreakerManager* gameManagerP);
	void ResetPos();
	void ReverseXMovement();
	void ReverseYMovement();
	void SetDirectedXMovement(Rectangle colRect);
	void PauseMovement();
	void ResumeMovement();
	void SetLoadValue(bool value);

	void SetSpeed(float speedP);
	float GetSpeed() const { return speed; }
	Vector2 GetPreviousPos() const { return previousPos; }

private:

	BreakerManager* gameManager{ nullptr };

	CircleComponent* drawCircleComp;
	CircleCollisionComponent* circleColComp;
	VelocityComponent* moveComp;
	BorderLimitComponent* borderLimitInterComp;

	float speed{ 300.0f };
	float directMultiplier{ 1.5f };
	Vector2 previousPos{ Vector2::zero };
};

