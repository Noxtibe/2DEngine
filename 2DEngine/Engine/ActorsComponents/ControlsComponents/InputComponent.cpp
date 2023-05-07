#include "InputComponent.h"
#include <SDL_scancode.h>
#include <Engine/Game.h>
#include <Engine/Maths/Maths.h>

void InputComponent::update(float dt)
{
	if (activateYAxis)
	{
		velocity.y = 0.0f;
		if (owner.getGame().isKeyDown(forwardKey))
		{
			velocity.y = -1.0f;
		}
		else if (owner.getGame().isKeyDown(backKey))
		{
			velocity.y = 1.0f;
		}
	}

	if (activateXAxis)
	{
		velocity.x = 0.0f;
		if (owner.getGame().isKeyDown(rightKey))
		{
			velocity.x = 1.0f;
		}
		else if (owner.getGame().isKeyDown(leftKey))
		{
			velocity.x = -1.0f;
		}
	}

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

void InputComponent::setForwardKey(SDL_Scancode key)
{
	forwardKey = key;
}

void InputComponent::setBackKey(SDL_Scancode key)
{
	backKey = key;
}

void InputComponent::setRightKey(SDL_Scancode key)
{
	rightKey = key;
}

void InputComponent::setLeftKey(SDL_Scancode key)
{
	leftKey = key;
}

void InputComponent::setClockwiseKey(SDL_Scancode key)
{
	clockwiseKey = key;
}

void InputComponent::setCounterClockwiseKey(SDL_Scancode key)
{
	counterClockwiseKey = key;
}