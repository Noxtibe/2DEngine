#pragma once
#include "LoadComponent.h"
#include <Engine/Maths/Rectangle.h>
#include <Engine/Utilitaire/Color.h>

class RectangleComponent : public LoadComponent
{

public:

	RectangleComponent(Actor* ownerP, Rectangle rectP, Color colorP, int drawOrderP = 100);
	virtual ~RectangleComponent();
	RectangleComponent() = delete;
	RectangleComponent(const RectangleComponent&) = delete;
	RectangleComponent& operator=(const RectangleComponent&) = delete;

	virtual void setRect(const Rectangle rectP);
	virtual void setColor(const Color colorP);
	virtual void draw(RendererSDL& renderer);

	Rectangle getRect() const { return rect; }
	Color getColor() const { return color; }

protected:

	Rectangle rect;
	Color color;
};

