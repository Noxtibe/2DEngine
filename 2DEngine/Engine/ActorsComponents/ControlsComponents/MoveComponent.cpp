#include "MoveComponent.h"
#include <Engine/Maths/Maths.h>
#include <Engine/ActorsComponents/Actor.h>

void MoveComponent::rewindLastMovement(bool rewindX, bool rewindY)
{
	Vector2 reverted_pos = getCustomRewindPosition(rewindX, rewindY);

	owner.setPosition(reverted_pos);
}

Vector2 MoveComponent::getCustomRewindPosition(bool xRewind, bool yRewind)
{
	return Vector2
	{
		   xRewind ? actorPosBeforeMovement.x : owner.getPosition().x,
		   yRewind ? actorPosBeforeMovement.y : owner.getPosition().y
	};
}

void MoveComponent::setActivateXMovement(bool activate)
{
	activateXAxis = activate;
	if (!activateXAxis)
	{
		stopXMovement();
	}
}

void MoveComponent::setActivateYMovement(bool activate)
{
	activateYAxis = activate;
	if (!activateYAxis)
	{
		stopYMovement();
	}
}

void MoveComponent::stopXMovement()
{
}

void MoveComponent::stopYMovement()
{
}

void MoveComponent::reverseXMovement()
{
}

void MoveComponent::reverseYMovement()
{
}
