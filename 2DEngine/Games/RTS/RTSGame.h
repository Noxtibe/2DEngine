#pragma once
#include <Engine/ILoading.h>

class RTSGame : public ILoading
{

public:

	RTSGame() : ILoading() {}
	~RTSGame() {}
	RTSGame(const RTSGame&) = delete;
	RTSGame& operator=(const RTSGame&) = delete;

	void load(Game* game) override;
};

