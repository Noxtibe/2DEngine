#include "RectangleCollisionComponent.h"
#include <Engine/ActorsComponents/Actor.h>
#include "CircleCollisionComponent.h"
#include <Engine/Game.h>
#include <Engine/Utilitaire/Log.h>
#include <Engine/Maths/Maths.h>

RectangleCollisionComponent::RectangleCollisionComponent(Actor* ownerP) : Component(ownerP)
{
}

Rectangle RectangleCollisionComponent::getTransformedRectangle() const
{
	return Rectangle{
		owner.getPosition().x + rectangle.x,
		owner.getPosition().y + rectangle.y,
		owner.getScale() * rectangle.width,
		owner.getScale() * rectangle.height
	};
}

void RectangleCollisionComponent::setRectangle(Rectangle rectangleP)
{
	rectangle = rectangleP;
}

bool RectangleCollisionComponent::intersectWithPoint(const Vector2& point) const
{
	Rectangle scaled_rect = getTransformedRectangle();
	return point.x >= scaled_rect.x && point.x <= scaled_rect.x + scaled_rect.width
		&& point.y >= scaled_rect.y && point.y <= scaled_rect.y + scaled_rect.height;
}

bool RectangleCollisionComponent::intersectWithCircleCollision(const CircleCollisionComponent& collision) const
{
	Rectangle scaled_rect = getTransformedRectangle();
	float half_width = scaled_rect.width / 2;
	float half_height = scaled_rect.height / 2;
	float circle_radius = collision.getRadius();
	Vector2 circle_center = collision.getCenter();

	Vector2 rect_center = Vector2{ scaled_rect.x + half_width, scaled_rect.y + half_height };
	Vector2 circle_distance = Vector2{ fabs(circle_center.x - rect_center.x), fabs(circle_center.y - rect_center.y) };

	if (circle_distance.x > (half_width + circle_radius)) return false;
	if (circle_distance.y > (half_height + circle_radius)) return false;

	if (circle_distance.x <= (half_width)) return true;
	if (circle_distance.y <= (half_height)) return true;

	float corner_distance_sq = (circle_distance.x - half_width) * (circle_distance.x - half_width)
		+ (circle_distance.y - half_height) * (circle_distance.y - half_height);
	return (corner_distance_sq <= (circle_radius * circle_radius));
}

bool RectangleCollisionComponent::intersectWithRectCollision(const RectangleCollisionComponent& collision) const
{
	Rectangle scaled_rect_1 = getTransformedRectangle();
	Rectangle scaled_rect_2 = collision.getTransformedRectangle();

	return intersectWithPoint(Vector2{ scaled_rect_2.x, scaled_rect_2.y })
		|| intersectWithPoint(Vector2{ scaled_rect_2.x + scaled_rect_2.width, scaled_rect_2.y })
		|| intersectWithPoint(Vector2{ scaled_rect_2.x, scaled_rect_2.y + scaled_rect_2.height })
		|| intersectWithPoint(Vector2{ scaled_rect_2.x + scaled_rect_2.width, scaled_rect_2.y + scaled_rect_2.height })
		|| collision.intersectWithPoint(Vector2{ scaled_rect_1.x, scaled_rect_1.y });
}

bool RectangleCollisionComponent::intersectWithY(const float y) const
{
	Rectangle scaled_rect = getTransformedRectangle();
	return y >= scaled_rect.y && y <= scaled_rect.y + scaled_rect.height;
}

bool RectangleCollisionComponent::intersectWithX(const float x) const
{
	Rectangle scaled_rect = getTransformedRectangle();
	return x >= scaled_rect.x && x <= scaled_rect.x + scaled_rect.width;
}

float RectangleCollisionComponent::nearestYPosOfY(const float y) const
{
	Rectangle scaled_rect = getTransformedRectangle();
	float y_center = scaled_rect.y + scaled_rect.height / 2.0f;
	if (y_center > y)
	{
		return y - rectangle.y;
	}
	else
	{
		return y - rectangle.y - scaled_rect.height;
	}
}

float RectangleCollisionComponent::nearestXPosOfX(const float x) const
{
	Rectangle scaled_rect = getTransformedRectangle();
	float x_center = scaled_rect.x + scaled_rect.width / 2.0f;
	if (x_center > x)
	{
		return x - rectangle.x;
	}
	else
	{
		return x - rectangle.x - scaled_rect.width;
	}
}
