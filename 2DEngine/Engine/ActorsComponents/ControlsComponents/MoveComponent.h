#pragma once
#include <Engine/ActorsComponents/Component.h>
#include <Engine/Maths/Vector2.h>

class MoveComponent : public Component
{

public:

	MoveComponent(Actor* ownerP, int updateOrderP = 10) : Component(ownerP, updateOrderP) {}
	MoveComponent() = delete; // By default, update before other components
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	void rewindLastMovement(bool rewindX, bool rewindY);
	Vector2 getCustomRewindPosition(bool xRewind, bool yRewind);
	Vector2 getBeforeLastMovementPosition() const { return actorPosBeforeMovement; }

	void setActivateXMovement(bool activate);
	bool getActivateXMovement() const { return activateXAxis; }
	void setActivateYMovement(bool activate);
	bool getActivateYMovement() const { return activateYAxis; }

	virtual void stopXMovement();
	virtual void stopYMovement();
	virtual void reverseXMovement();
	virtual void reverseYMovement();

protected:

	bool activateXAxis{ true };
	bool activateYAxis{ true };

	Vector2 actorPosBeforeMovement{ Vector2::zero };
};