#include "BBPaddle.h"
#include <Engine/Maths/Rectangle.h>

BBPaddle::BBPaddle() : Actor()
{
	Rectangle rect = Rectangle{ -50.0f, 0.0f, 100.0f, 10.0f };

	drawRectComp = new RectangleComponent(this, rect, Color::green);

	rectColComp = new RectangleCollisionComponent(this);
	rectColComp->setRectangle(rect);

	mouseMoveComp = new MouseComponent(this);
	mouseMoveComp->setActivateYMovement(false);

	borderLimitInterComp = new BorderLimitComponent(this, mouseMoveComp, rectColComp);
	borderLimitInterComp->setInteractions(BorderLimitInteractions::SmoothBlock, BorderLimitInteractions::SmoothBlock, BorderLimitInteractions::SmoothBlock, BorderLimitInteractions::SmoothBlock);
	borderLimitInterComp->autoUpdate = true;
}

void BBPaddle::SetLoadValue(bool value)
{
	drawRectComp->setWillLoad(value);
}
