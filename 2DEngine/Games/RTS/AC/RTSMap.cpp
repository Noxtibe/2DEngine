#include "RTSMap.h"
#include <Engine/ActorsComponents/GridComponent/GridTileRectangle.h>
#include <Engine/ActorsComponents/GridComponent/GridTileSprite.h>
#include <Engine/AssetsManager/Assets.h>

RTSMap::RTSMap(GridMap* gridMapP)
{
	gridComp = new GridComponent(this, gridMapP);
	gridComp->setTileSize(Vector2{ 40.0f, 40.0f });

	gridComp->setTileTraduction(1, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_tree_top")), true });
	gridComp->setTileTraduction(2, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_grass")), true });
	gridComp->setTileTraduction(3, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_big_tree_tl")), true });
	gridComp->setTileTraduction(4, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_big_tree_tr")), true });
	gridComp->setTileTraduction(5, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_tree_mid")), true });
	gridComp->setTileTraduction(6, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_bush")), true });
	gridComp->setTileTraduction(7, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_big_tree_ml")), true });
	gridComp->setTileTraduction(8, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_big_tree_mr")), true });
	gridComp->setTileTraduction(9, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_tree_bot")), true });
	gridComp->setTileTraduction(10, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_small_tree")), true });
	gridComp->setTileTraduction(11, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_big_tree_bl")), true });
	gridComp->setTileTraduction(12, new TileTraduction{ new GridTileSprite(Assets::getTexture("t_big_tree_br")), true });

	gridComp->setAstarTraduction(2, AstarTraduction{ true, 10, 14 });
}