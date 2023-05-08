#pragma once
#include "InputComponent.h"
#include <SDL_scancode.h>

//  Does not controls X and Y axis disabling
//  Override all modifications done by the actors rotation

class RotationComponent : public InputComponent
{

public:

	RotationComponent(Actor* ownerP, float startAngleP = 0.0f, int updateOrderP = 10);
	RotationComponent() = delete;
	RotationComponent(const RotationComponent&) = delete;
	RotationComponent& operator=(const RotationComponent&) = delete;

	void update(float dt) override;

	void setInputValues(float forwardSpeedInputValueP, float backSpeedInputValue, float angleInputValueP);
	void setMotionValues(float persistantSpeedLooseP, float minSpeedForFullControlP);

	void setArbitraryAngle(float arbitraryAngle);

private:

	void applyRotationChange();
	bool isUserInputItsDirection();

	float angle;
	float forwardSpeedInputValue{ 1.0f };
	float backSpeedInputValue{ 0.5f };
	float angleInputValue{ 0.05f };
	float persistantSpeedLoose{ 0.45f }; //  the fraction of speed that is lost each second
	float minSpeedForFullControl{ 15.0f };
};

