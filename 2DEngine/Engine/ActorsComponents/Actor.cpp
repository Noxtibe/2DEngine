#include "Actor.h"
#include <algorithm>
#include <Engine/Game.h>
#include "Component.h"
#include <Engine/Maths/Maths.h>

Actor::Actor() : game(Game::instance())
{
	game.addActor(this);
}

Actor::~Actor()
{
	game.removeActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::setPosition(Vector3 positionP)
{
	position = positionP;
	mustRecomputeWorldTransform = true;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
	mustRecomputeWorldTransform = true;
}

void Actor::setRotation(Quaternion rotationP)
{
	rotation = rotationP;
	mustRecomputeWorldTransform = true;
}

void Actor::set2DRotation(float rotation2DP)
{
	rotation2D = rotation2DP;
	Quaternion newRotation(Vector3::unitZ, rotation2D);
	rotation = newRotation;
	mustRecomputeWorldTransform = true;
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		updateComponents(dt);
		updateActor(dt);
		updateTransformMatrix();
	}
}

void Actor::updateComponents(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::debugComponents(RendererSDL& renderer)
{
	for (auto component : components)
	{
		component->debug(renderer);
	}
}

void Actor::updateActor(float dt)
{
}

void Actor::updateTransformMatrix()
{
	if (!mustRecomputeWorldTransform) return;

	mustRecomputeWorldTransform = false;
	worldTransform = Matrix4::createScale(scale);
	worldTransform *= Matrix4::createFromQuaternion(rotation);
	worldTransform *= Matrix4::createTranslation(position);
}

void Actor::addComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}

Vector3 Actor::getForward() const
{
	return Vector3::transform(Vector3::unitX, rotation);
}

Vector3 Actor::getRight() const
{
	return Vector3::transform(Vector3::unitY, rotation);
}