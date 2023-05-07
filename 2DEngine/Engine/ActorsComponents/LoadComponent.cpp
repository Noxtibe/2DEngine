#include "LoadComponent.h"
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/Game.h>

LoadComponent::LoadComponent(Actor* ownerP, int loadOrderP) : Component(ownerP), loadOrder(loadOrderP)
{
	owner.getGame().getRenderer().addLoadComponent(this);
}

LoadComponent::~LoadComponent()
{
	owner.getGame().getRenderer().removeLoadComponent(this);
}

void LoadComponent::load(RendererSDL& renderer)
{
}

void LoadComponent::setWillLoad(bool willLoadP)
{
	willLoad = willLoadP;
}