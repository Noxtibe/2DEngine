#include "MouseComponent.h"
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/Game.h>

void MouseComponent::update(float dt)
{
	actorPosBeforeMovement = owner.getPosition();
	Vector2 new_position = owner.getPosition();

	Vector2 mouse_position = owner.getGame().getMousePosition();

	if (activateXAxis)
	{
		new_position.x = mouse_position.x;
	}

	if (activateYAxis)
	{
		new_position.y = mouse_position.y;
	}

	owner.setPosition(new_position);
}