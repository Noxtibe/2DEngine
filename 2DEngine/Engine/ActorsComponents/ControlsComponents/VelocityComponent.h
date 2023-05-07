#pragma once
#include "MoveComponent.h"

class VelocityComponent : public MoveComponent
{

public:

	VelocityComponent(Actor* ownerP, int updateOrderP = 10) : MoveComponent(ownerP, updateOrderP) {}
	VelocityComponent() = delete;
	VelocityComponent(const VelocityComponent&) = delete;
	VelocityComponent& operator=(const VelocityComponent&) = delete;

	Vector2 getVelocity() const { return velocity; }
	void setVelocity(Vector2 velocityP);
	float getSpeed() const { return speed; }
	void setSpeed(float speedP);

	virtual void update(float dt) override;

	void stopXMovement() override;
	void stopYMovement() override;
	void reverseXMovement() override;
	void reverseYMovement() override;

protected:

	Vector2 velocity{ Vector2::zero };
	float speed{ 0.0f };

};

