#pragma once
#include "MoveComponent.h"

class DestinationComponent : public MoveComponent
{

public:

	DestinationComponent(Actor* ownerP, int updateOrderP = 10) : MoveComponent(ownerP, updateOrderP) {}
	DestinationComponent() = delete;
	DestinationComponent(const DestinationComponent&) = delete;
	DestinationComponent& operator=(const DestinationComponent&) = delete;

	void setSpeed(float speedP);
	float getSpeed() const { return speed; }
	void setDestination(Vector2 destinationP);
	Vector2 getDestination() const { return destination; }
	bool isOnDestination() const { return !needToMove; }

	virtual void update(float dt) override;

protected:

	float speed{ 0.0f };
	Vector2 destination{ Vector2::zero };
	bool needToMove{ false };
};

