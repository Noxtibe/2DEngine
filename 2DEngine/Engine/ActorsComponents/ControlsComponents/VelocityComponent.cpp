#include "VelocityComponent.h"
#include <Engine/Maths/Maths.h>
#include <Engine/ActorsComponents/Actor.h>

void VelocityComponent::setVelocity(Vector2 velocityP)
{
	velocity = velocityP;
}

void VelocityComponent::setSpeed(float speedP)
{
	speed = speedP;
}

void VelocityComponent::update(float dt)
{
	actorPosBeforeMovement = owner.getPosition();
	if (!Maths::nearZero(speed))
	{
		if (!Maths::nearZero(velocity.lengthSq()))
		{
			velocity.normalize();
		}
		Vector2 new_position = owner.getPosition() + velocity * speed * dt;
		owner.setPosition(new_position);
	}
}

void VelocityComponent::stopXMovement()
{
	velocity.x = 0.0f;
}

void VelocityComponent::stopYMovement()
{
	velocity.y = 0.0f;
}

void VelocityComponent::reverseXMovement()
{
	velocity.x = -velocity.x;
}

void VelocityComponent::reverseYMovement()
{
	velocity.y = -velocity.y;
}
