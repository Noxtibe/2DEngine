#include "RTSInput.h"
#include <Engine/Game.h>
#include <Engine/AssetsManager/Assets.h>
#include <Engine/ActorsComponents/GridComponent/GridTileSprite.h>
#include <Algo/AStar.h>
#include <Engine/Maths/Vector2Int.h>
#include <vector>

RTSInput::RTSInput(RTSManager* managerP, RTSMap* mapP) : Actor(), manager(managerP), map(mapP)
{
	player = new RTSPlayerTurn(Assets::getTexture("player"));
	player->setPosition(Vector2{ 1232.0f, 720.0f });

	camera = new RTSCamera(player);


	aimDirGrid = new GridComponent(this, 1000);
	aimDirGrid->setTileSize(map->GetGridComp().getTileSize());
	aimDirGrid->setGridSize(map->GetGridComp().getGridSize());
	aimDirGrid->setTileTraduction(1, new TileTraduction{ new GridTileSprite(Assets::getTexture("aimValid")), false });
	aimDirGrid->setTileTraduction(2, new TileTraduction{ new GridTileSprite(Assets::getTexture("aimInvalid")), false });
	aimDirGrid->setTileTraduction(3, new TileTraduction{ new GridTileSprite(Assets::getTexture("pathFinding")), false });

	managerP->AddTurnBasedActor(player);

	managerP->ForceGlobalTurnAction();
}

void RTSInput::updateActor(float dt)
{
	aimDirGrid->resetToZero();

	GridComponent& map_grid = map->GetGridComp();


	if (player->HasMovementWaiting())
	{
		if (getGame().isKeyPressed(SDL_MOUSE_LEFT_BUTTON))
		{
			player->ForceClearMovement();
		}

		if (!player->MovingBetweenTiles())
		{
			manager->PlayGlobalTurnAction();
		}



		int map_player_x, map_player_y = 0;
		map_grid.screenPointAsGridCoordinates(player->getPosition(), &map_player_x, &map_player_y);
		Vector2Int map_player = { map_player_x, map_player_y };
		if (map_player != lastDestinationRegistered)
		{
			std::vector<Vector2Int> dir_way = AStar::AStarGridComp(map_grid, map_player, lastDestinationRegistered, true);

			while (!dir_way.empty())
			{
				aimDirGrid->setGridElement(*(dir_way.end() - 1), 3);
				dir_way.pop_back();
			}
		}
	}
	else
	{
		Vector2 mouse_pos = getGame().getMousePosition();

		if (player->IsUnderMouse(mouse_pos)) return;
		int map_mouse_x, map_mouse_y = 0;
		int map_player_x, map_player_y = 0;

		if (map_grid.intersectWithScreenPoint(mouse_pos, &map_mouse_x, &map_mouse_y))
		{
			Vector2Int map_mouse = { map_mouse_x, map_mouse_y };

			if (map_grid.getAstarTraduction(map_mouse_x, map_mouse_y).walkable)
			{
				map_grid.screenPointAsGridCoordinates(player->getPosition(), &map_player_x, &map_player_y);
				Vector2Int map_player = { map_player_x, map_player_y };

				std::vector<Vector2Int> dir_way = AStar::AStarGridComp(map_grid, map_player, map_mouse, true);

				if (dir_way.size() == 1 && dir_way[0] == map_player)
				{
					aimDirGrid->setGridElement(map_mouse_x, map_mouse_y, 2);
				}
				else
				{
					if (getGame().isKeyPressed(SDL_MOUSE_LEFT_BUTTON))
					{
						std::vector<Vector2> move_list;
						Vector2 grid_tile_size = map_grid.getTileSize();
						for (auto iter : dir_way)
						{
							move_list.push_back(Vector2{ iter.x * grid_tile_size.x + grid_tile_size.x / 2.0f , iter.y * grid_tile_size.y + grid_tile_size.y / 2.0f });
						}
						std::reverse(move_list.begin(), move_list.end());

						player->SetMovementList(move_list);
						lastDestinationRegistered = map_mouse;
					}

					aimDirGrid->setGridElement(map_mouse_x, map_mouse_y, 1);
					dir_way.pop_back();
					while (!dir_way.empty())
					{
						aimDirGrid->setGridElement(*(dir_way.end() - 1), 3);
						dir_way.pop_back();
					}
				}
			}
			else
			{
				aimDirGrid->setGridElement(map_mouse_x, map_mouse_y, 2);
			}
		}
	}
}
