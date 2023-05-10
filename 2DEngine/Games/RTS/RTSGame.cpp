#include "RTSGame.h"
#include <Engine/Game.h>
#include <Engine/AssetsManager/Assets.h>
#include "AC/RTSManager.h"
#include "AC/RTSInput.h"
#include "AC/RTSMap.h"
#include "AC/RTSCamera.h"

void RTSGame::load(Game* game)
{
	Assets::setAssetsPath("Games/RTS/Assets/");

	// Player related Loading

	Assets::loadTexture(game->getRenderer(), "AimValid.png", "aimValid");
	Assets::loadTexture(game->getRenderer(), "AimInvalid.png", "aimInvalid");
	Assets::loadTexture(game->getRenderer(), "pathFinding.png", "pathFinding");
	Assets::loadTexture(game->getRenderer(), "Player.png", "player");

	// Map Loading

	Assets::loadGridMap("RTSMap2.lua", "RTSMap2");

	// Tiling Assets Loading

	Assets::loadTexture(game->getRenderer(), "TilingAssets/grass.png", "t_grass");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/bush.png", "t_bush");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/small_tree.png", "t_small_tree");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/tree_bot.png", "t_tree_bot");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/tree_mid.png", "t_tree_mid");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/tree_top.png", "t_tree_top");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/big_tree_bl.png", "t_big_tree_bl");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/big_tree_br.png", "t_big_tree_br");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/big_tree_ml.png", "t_big_tree_ml");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/big_tree_mr.png", "t_big_tree_mr");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/big_tree_tl.png", "t_big_tree_tl");
	Assets::loadTexture(game->getRenderer(), "TilingAssets/big_tree_tr.png", "t_big_tree_tr");

	auto manager = new RTSManager();
	auto map = new RTSMap(Assets::getGridMap("RTSMap2"));

	auto player_inputs = new RTSInput(manager, map);
}