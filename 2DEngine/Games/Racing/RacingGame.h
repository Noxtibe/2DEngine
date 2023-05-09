#pragma once
#include <Engine/ILoading.h>

class RacingGame : public ILoading
{
public:
	RacingGame() : ILoading() {}
	~RacingGame() {}
	RacingGame(const RacingGame&) = delete;
	RacingGame& operator=(const RacingGame&) = delete;

	void load(Game* game) override;
};

