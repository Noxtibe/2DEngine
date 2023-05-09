#include "PlayerPaddle.h"

PlayerPaddle::PlayerPaddle() : Paddle()
{
	mouseComp = new MouseComponent(this);
	mouseComp->setActivateXMovement(false);

	borderLimitInterComp = new BorderLimitComponent(this, mouseComp, rectColComp);
	borderLimitInterComp->setInteractions(BorderLimitInteractions::SmoothBlock, BorderLimitInteractions::SmoothBlock, BorderLimitInteractions::SmoothBlock, BorderLimitInteractions::SmoothBlock);
	borderLimitInterComp->autoUpdate = true;
}