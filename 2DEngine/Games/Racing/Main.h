#pragma once
#include <Engine/Game.h>
#include "RacingGame.h"

void launch()
{
	auto& game = Game::instance();
	bool is_game_init = game.initialize("Racing Game", 800, 600, Color::black);

	if (is_game_init)
	{
		game.loadGame(new RacingGame());
		game.loop();
		game.unload();
	}

	game.close();
}