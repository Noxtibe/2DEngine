#include "AStar.h"
#include <Engine/ActorsComponents/GridComponent/GridComponent.h>
#include <algorithm>

bool compareTiles(const Tile& a, const Tile& b)
{
	return b.score < a.score;
}

std::vector<Vector2Int> AStar::AStarGridComp(const GridComponent& grid, Vector2Int start, Vector2Int end, bool reverseReturn, int heuristicValue)
{
	Vector2Int grid_size = grid.getGridSize();
	std::vector<Vector2Int> way;
	way.push_back(start);

	if (start.x < 0 || start.x >= grid_size.x || start.y < 0 || start.y >= grid_size.y ||
		end.x < 0 || end.x >= grid_size.x || end.y < 0 || end.y >= grid_size.y || start == end)
	{
		return way; //  will return a "no way" if astar can't be compute with those start and end on this grid
	}


	std::unordered_map<Vector2Int, Tile, Vector2IntHash, Vector2IntEqual> checked_tiles;
	std::vector<Tile> registered_tiles;
	std::unordered_map<Vector2Int, Tile, Vector2IntHash, Vector2IntEqual> already_registered_tiles;

	registered_tiles.push_back(Tile{ start, 0, 0, 0, start });
	Tile current_check;

	while (registered_tiles.size() > 0) //  will run while there is accessible tiles to check (will return before if it finds a way)
	{
		std::sort(registered_tiles.begin(), registered_tiles.end(), compareTiles); //  put the lowest score tile at the end of the list
		current_check = *(registered_tiles.end() - 1); //  select the lowest score tile
		registered_tiles.pop_back(); //  remove the selected tile of the tile to check list

		if (checked_tiles.find(current_check.pos) != checked_tiles.end()) continue;

		if (current_check.pos == end) //  check if the lowest score tile is the end tile
		{
			way.clear();
			Tile way_backward = current_check;
			while (way_backward.pos != start)
			{
				way.push_back(way_backward.pos);
				way_backward = checked_tiles[way_backward.previousTilePos];
			}

			if (reverseReturn)
			{
				std::reverse(way.begin(), way.end());
			}

			return way;
		}

		for (int x = Maths::max(current_check.pos.x - 1, 0); x <= Maths::min(current_check.pos.x + 1, grid_size.x - 1); x++)
		{
			for (int y = Maths::max(current_check.pos.y - 1, 0); y <= Maths::min(current_check.pos.y + 1, grid_size.y - 1); y++)
			{
				if (Vector2Int{ x, y } == current_check.pos) continue; //  check if the tile to register isn't the current checked tile
				if (checked_tiles.find(Vector2Int{ x, y }) != checked_tiles.end()) continue; //  check if the tile to register hasn't been already checked

				AstarTraduction check_traduction = grid.getAstarTraduction(x, y);
				if (!check_traduction.walkable) continue; //  check if the tile to register is walkable

				bool check_diagonal = x != current_check.pos.x && y != current_check.pos.y;
				if (check_diagonal && !grid.getAstarTraduction(current_check.pos.x, y).walkable && !grid.getAstarTraduction(x, current_check.pos.y).walkable) continue;
				//  check if the tile to register is accessible whithout passing by closed corners

				int local_cost = check_diagonal ? check_traduction.diagonal : check_traduction.straight;
				int heuristic = (Maths::abs(end.x - x) + abs(end.y - y)) * heuristicValue;

				Tile check_tile = Tile{ Vector2Int{x, y}, current_check.cost + local_cost, heuristic, current_check.cost + local_cost + heuristic, current_check.pos };

				if (already_registered_tiles.find(Vector2Int{ x, y }) != already_registered_tiles.end() //  check if the tile to register has already been registered
					&& (already_registered_tiles[Vector2Int{ x, y }].score <= check_tile.score)) continue; //  and if so, check if the new score for this tile is bigger

				registered_tiles.push_back(check_tile);
				already_registered_tiles[Vector2Int{ x, y }] = check_tile;
			}
		}

		checked_tiles[current_check.pos] = current_check; //  add the current checked tile to the list of checked tiles before switching to a new check
	}

	return way; //  will return a "no way" if there is no way possible from start to end on this grid
}
