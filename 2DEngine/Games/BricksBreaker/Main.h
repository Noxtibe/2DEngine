#pragma once
#include <Engine/Game.h>
#include "BricksBreakerGame.h"

void launch()
{
	auto& game = Game::instance();
	bool is_game_init = game.initialize("Bricks Breaker", 800, 600, Color::black);

	if (is_game_init)
	{
		game.loadGame(new BricksBreakerGame());
		game.loop();
		game.unload();
	}

	game.close();
}