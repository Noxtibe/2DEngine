#pragma once
#include <SDL_stdinc.h>

class Actor;
class RendererSDL;

class Component
{

public:

	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void update(float dt);
	virtual void debug(RendererSDL& renderer);

protected:

	Actor& owner;
	int updateOrder;		// Order of the component in the actor's updateComponent method
};