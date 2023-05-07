#include "Component.h"
#include "Actor.h"
#include <Engine/RendererSDL.h>

Component::Component(Actor* ownerP, int updateOrderP) : owner(*ownerP), updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::update(float dt)
{
}

void Component::debug(RendererSDL& renderer)
{

}