/*#pragma once
#include <Engine/Game.h>
#include "RTSGame.h"

void launch()
{
	auto& game = Game::instance();
	bool is_game_init = game.initialize("RTS", 1600, 800, Color::black);

	if(is_game_init)
	{
		game.loadGame(new RTSGame());
		game.loop();
		game.unload();
	}

	game.close();
}*/