#pragma once
#include "MoveComponent.h"

class MouseComponent : public MoveComponent
{

public:

	MouseComponent(Actor* ownerP, int updateOrderP = 10) : MoveComponent(ownerP, updateOrderP) {}
	MouseComponent() = delete;
	MouseComponent(const MouseComponent&) = delete;
	MouseComponent& operator=(const MouseComponent&) = delete;

	void update(float dt) override;
};