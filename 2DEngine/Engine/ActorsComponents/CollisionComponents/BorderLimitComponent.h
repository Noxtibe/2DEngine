#pragma once
#include "../Component.h"
#include "Engine/ActorsComponents/ControlsComponents/MoveComponent.h"
#include <Engine/ActorsComponents/CollisionComponents/ICollision.h>

enum class BorderLimitInteractions
{
	Block, //  this interaction will nullify the movement that causes the interaction (will return 0)
	Bounce, //  this interaction will nullify the movement that causes the interaction and negate the x or y velocity to produce a bounce effect (will return 0)
	SmoothBlock, //  like 'Block', but will bring the actor the nearest possible of the border (ideal for high velocity or mouse controlled actors, but heavier for the computer) (will return 0)
	SmoothBounce, //  like 'SmoothBlock', but will the negation of velocity to produce the bounce effect (will return 0)
	Return //  this interaction will return a value depending of the border that interact with the collision (1 for up, 2 for down, 3 for left, 4 for right) 
};

class BorderLimitComponent : public Component
{

public:

	BorderLimitComponent(Actor* ownerP, MoveComponent* moveComponentP, ICollision* colComponentP) : Component(ownerP, 200), moveComponent(moveComponentP), colComponent(colComponentP) {}
	BorderLimitComponent() = delete;
	BorderLimitComponent(const BorderLimitComponent&) = delete;
	BorderLimitComponent& operator=(const BorderLimitComponent&) = delete;

	void setInteractions(BorderLimitInteractions upInteractionP, BorderLimitInteractions downInteractionP, BorderLimitInteractions leftInteractionP, BorderLimitInteractions rightInteractionP);
	int checkBordersInteractions();

	void update(float dt) override;
	bool autoUpdate = false; //  if true, the update will run the 'CheckBordersInteractions' function (the block and bounce intersections types will work, but not the return one)

private:

	MoveComponent* moveComponent;
	ICollision* colComponent;

	BorderLimitInteractions upInteraction = BorderLimitInteractions::Return;
	BorderLimitInteractions downInteraction = BorderLimitInteractions::Return;
	BorderLimitInteractions leftInteraction = BorderLimitInteractions::Return;
	BorderLimitInteractions rightInteraction = BorderLimitInteractions::Return;
};

