#pragma once
#include "VelocityComponent.h"
#include <SDL_scancode.h>

class InputComponent : public VelocityComponent
{

public:

	InputComponent(Actor* ownerP, int updateOrderP = 10) : VelocityComponent(ownerP, updateOrderP) {}
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	virtual void update(float dt) override;


	void setForwardKey(SDL_Scancode key);
	void setBackKey(SDL_Scancode key);
	void setRightKey(SDL_Scancode key);
	void setLeftKey(SDL_Scancode key);
	//void setClockwiseKey(SDL_Scancode key);
	//void setCounterClockwiseKey(SDL_Scancode key);

	

protected:

	SDL_Scancode forwardKey{ SDL_SCANCODE_W };
	SDL_Scancode backKey{ SDL_SCANCODE_S };
	SDL_Scancode rightKey{ SDL_SCANCODE_D };
	SDL_Scancode leftKey{ SDL_SCANCODE_A };

	//SDL_Scancode clockwiseKey;
	//SDL_Scancode counterClockwiseKey;
};