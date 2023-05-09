#pragma once
#include <Engine/ILoading.h>

class BricksBreakerGame : public ILoading
{

public:

	BricksBreakerGame() : ILoading() {}
	~BricksBreakerGame() {}
	BricksBreakerGame(const BricksBreakerGame&) = delete;
	BricksBreakerGame& operator=(const BricksBreakerGame&) = delete;

	void load(Game* game) override;
};