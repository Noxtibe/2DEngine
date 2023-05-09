#include "Paddle.h"
#include <Engine/Maths/Rectangle.h>

Paddle::Paddle() : Actor()
{
	Rectangle rect = Rectangle{ 0.0f, -50.0f, 10.0f, 100.0f };

	loadRectComp = new RectangleComponent(this, rect, Color::white);

	rectColComp = new RectangleCollisionComponent(this);
	rectColComp->setRectangle(rect);
}

void Paddle::SetLoadValue(bool value)
{
	loadRectComp->setWillLoad(value);
}
