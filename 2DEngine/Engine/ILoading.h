#pragma once

class Game;

class ILoading
{
public:
	virtual ~ILoading() {}

	virtual void load(Game* game) = 0;
};