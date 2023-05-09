#pragma once
#include <Engine/ILoading.h>

class PongGame : public ILoading
{

public:

	PongGame() : ILoading() {}
	~PongGame() {}
	PongGame(const PongGame&) = delete;
	PongGame& operator=(const PongGame&) = delete;

	void load(Game* game) override;
};

