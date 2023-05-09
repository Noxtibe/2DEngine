#include "RacingGame.h"
#include <Engine/AssetsManager/Assets.h>
#include <Engine/Game.h>
#include "AC/RCTrack.h"
#include "AC/PlayerCar.h"
#include "AC/RCManager.h"

void RacingGame::load(Game* game)
{
	Assets::setAssetsPath("Games/Racing/Assets/");

	Assets::loadFont("Pixeled.ttf", "pixeled30", 30);
	Assets::loadGridMap("RacingTrack.lua", "track");
	Assets::loadTexture(game->getRenderer(), "redcar.png", "player1Car");
	Assets::loadTexture(game->getRenderer(), "greencar.png", "player2Car");
	Assets::loadTexture(game->getRenderer(), "track_road.png", "track_road");
	Assets::loadTexture(game->getRenderer(), "track_wall.png", "track_wall");
	Assets::loadTexture(game->getRenderer(), "track_finish.png", "track_finish");
	Assets::loadTexture(game->getRenderer(), "track_grass.png", "track_grass");
	Assets::loadTexture(game->getRenderer(), "track_tree.png", "track_tree");

	auto track = new RCTrack(Assets::getGridMap("track"));

	auto player_one = new PlayerCar(Assets::getTexture("player1Car"), false);
	auto player_two = new PlayerCar(Assets::getTexture("player2Car"), true);

	auto manager = new RCManager(track, player_one, player_two);

	game->getCamera().setCamPos(Vector2::zero);
}