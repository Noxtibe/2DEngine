#include "RotationComponent.h"
#include <Engine/Game.h>
#include <Engine/Maths/Maths.h>

RotationComponent::RotationComponent(Actor* ownerP, float startAngleP, int updateOrderP) : InputComponent(ownerP, updateOrderP)
{
	setArbitraryAngle(startAngleP);
}

void RotationComponent::update(float dt)
{
	if (owner.getGame().isKeyDown(forwardKey))
	{
		speed += forwardSpeedInputValue;
	}
	if (owner.getGame().isKeyDown(backKey))
	{
		speed -= backSpeedInputValue;
	}

	if (owner.getGame().isKeyDown(leftKey))
	{
		angle += Maths::abs(speed) > minSpeedForFullControl ? angleInputValue : angleInputValue * Maths::abs(speed) / minSpeedForFullControl;
		applyRotationChange();
	}
	if (owner.getGame().isKeyDown(rightKey))
	{
		angle -= Maths::abs(speed) > minSpeedForFullControl ? angleInputValue : angleInputValue * Maths::abs(speed) / minSpeedForFullControl;
		applyRotationChange();
	}


	//  why does c++ is not capable of doing 'base.update(dt);' I am crying :((((((((((
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
	//  end of crying

	if (!Maths::nearZero(speed))
	{
		if (!isUserInputItsDirection())
		{
			if (Maths::abs(speed) > minSpeedForFullControl)
			{
				speed -= speed * persistantSpeedLoose * dt;
			}
			else
			{
				speed = 0.0f;
			}
		}
	}
}

void RotationComponent::setInputValues(float forwardSpeedInputValueP, float backSpeedInputValueP, float angleInputValueP)
{
	forwardSpeedInputValue = forwardSpeedInputValueP;
	backSpeedInputValue = backSpeedInputValueP;
	angleInputValue = angleInputValueP;
}

void RotationComponent::setMotionValues(float persistantSpeedLooseP, float minSpeedForFullControlP)
{
	persistantSpeedLoose = persistantSpeedLooseP;
	minSpeedForFullControl = minSpeedForFullControlP;
}

void RotationComponent::setArbitraryAngle(float arbitraryAngle)
{
	angle = arbitraryAngle;
	applyRotationChange();
}

void RotationComponent::applyRotationChange()
{
	velocity = Vector2{ Maths::cos(-angle), Maths::sin(-angle) };
	owner.set2DRotation(angle);
}

bool RotationComponent::isUserInputItsDirection()
{
	return speed > 0.0f && owner.getGame().isKeyDown(forwardKey) || speed < 0.0f && owner.getGame().isKeyDown(backKey);
}
