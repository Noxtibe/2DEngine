#include "RCTrack.h"
#include <Engine/Game.h>
#include <Engine/ActorsComponents/GridComponent/GridTileSprite.h>

RCTrack::RCTrack(GridMap* gridMapP) : gridMap(gridMapP)
{
	gridComp = new GridComponent(this, gridMapP);
	int screen_width = getGame().getScreenWidth();
	int screen_height = getGame().getScreenHeight();
	gridComp->setTileSize(Vector2{ static_cast<float>(screen_width) / gridMapP->getWidth(), static_cast<float>(screen_height) / gridMapP->getHeight() });

	gridComp->setTileTraduction(1, new TileTraduction{ new GridTileSprite(Assets::getTexture("track_road")), false });
	gridComp->setTileTraduction(2, new TileTraduction{ new GridTileSprite(Assets::getTexture("track_wall")), true });
	gridComp->setTileTraduction(3, new TileTraduction{ new GridTileSprite(Assets::getTexture("track_finish")), false });
	gridComp->setTileTraduction(4, new TileTraduction{ new GridTileSprite(Assets::getTexture("track_grass")), true });
	gridComp->setTileTraduction(5, new TileTraduction{ new GridTileSprite(Assets::getTexture("track_tree")), true });
}

void RCTrack::ResetTrack()
{
	gridComp->resetToGridMap(gridMap);
}

Vector2 RCTrack::GetPlayerStartPos(int startPosGridIndex)
{
	for (int x = 0; x < gridComp->getGridWidth(); x++)
	{
		for (int y = 0; y < gridComp->getGridHeight(); y++)
		{
			if (gridComp->getGridElement(x, y) == startPosGridIndex)
			{
				gridComp->setGridElement(x, y, 1);
				Vector2 tile_size = gridComp->getTileSize();
				return Vector2{ (x + 0.5f) * tile_size.x, (y + 0.5f) * tile_size.y };
			}
		}
	}

	return Vector2::zero;
}
