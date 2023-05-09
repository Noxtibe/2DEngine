#pragma once
#include <Engine/Game.h>
#include "PongGame.h"

void launch()
{
	auto& game = Game::instance();
	bool is_game_init = game.initialize("Pong", 800, 600, Color::black);

	if (is_game_init)
	{
		game.loadGame(new PongGame());
		game.loop();
		game.unload();
	}

	game.close();
}