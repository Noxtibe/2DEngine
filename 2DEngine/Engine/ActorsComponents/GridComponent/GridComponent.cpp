#include "GridComponent.h"
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/Game.h>
#include <Engine/Maths/Maths.h>
#include <Engine/ActorsComponents/CollisionComponents/CircleCollisionComponent.h>
#include <Engine/ActorsComponents/CollisionComponents/RectangleCollisionComponent.h>

GridComponent::GridComponent(Actor* ownerP, int drawOrderP) : LoadComponent(ownerP, drawOrderP)
{
	basicInitialization(ownerP);
}

GridComponent::GridComponent(Actor* ownerP, GridMap* gridMap, int drawOrderP) : LoadComponent(ownerP, drawOrderP)
{
	basicInitialization(ownerP);
	resetToGridMap(gridMap);
}

GridComponent::~GridComponent()
{
}

void GridComponent::basicInitialization(Actor* ownerP)
{
	tileTraduction[0] = new TileTraduction;
	astarTraduction[0] = AstarTraduction{ true, 10, 14 };
	astarTraduction[1] = AstarTraduction{ false, 0, 0 };
	gridRectCol = new RectangleCollisionComponent(ownerP, false);
	screenSize = Vector2{ static_cast<float>(owner.getGame().getScreenWidth()), static_cast<float>(owner.getGame().getScreenHeight()) };
}

void GridComponent::resetToGridMap(GridMap* gridMap)
{
	if (!gridMap) return;

	setGridSize(gridMap->getWidth(), gridMap->getHeight());
	vector<int> map_datas = gridMap->getMap();
	for (int i = 0; i < map_datas.size(); i++)
	{
		setGridElement(i % gridWidth, Maths::floor(i / gridWidth), map_datas[i]);
	}
}

void GridComponent::resetToZero()
{
	for (int i = 0; i < grid.size(); i++)
	{
		grid[i] = 0;
	}
}

void GridComponent::setGridSize(int gridWidthP, int gridHeightP)
{
	if (gridWidthP > 0 && gridHeightP > 0)
	{
		vector<int> new_grid;
		new_grid.resize(gridWidthP * gridHeightP);

		for (int i = 0; i < gridWidthP; i++)
		{
			for (int j = 0; j < gridHeightP; j++)
			{
				if (i < gridWidth && j < gridHeight)
				{
					new_grid[i * gridHeightP + j] = grid[i * gridHeight + j];
				}
				else
				{
					new_grid[i * gridHeightP + j] = 0;
				}
			}
		}

		grid.resize(gridWidthP * gridHeightP);
		grid = new_grid;

		gridWidth = gridWidthP;
		gridHeight = gridHeightP;

		resetGridRectCol();
	}
}

void GridComponent::setGridSize(Vector2Int gridSizeP)
{
	setGridSize(gridSizeP.x, gridSizeP.y);
}

bool GridComponent::setGridElement(int indexX, int indexY, int element)
{
	if (gridWidth > 0 && gridHeight > 0)
	{
		if (indexX >= 0 && indexX < gridWidth && indexY >= 0 && indexY < gridHeight)
		{
			grid[indexX * gridHeight + indexY] = element;
			return true;
		}
	}
	return false;
}

int GridComponent::getGridElement(int indexX, int indexY) const
{
	if (gridWidth > 0 && gridHeight > 0)
	{
		if (indexX >= 0 && indexX < gridWidth && indexY >= 0 && indexY < gridHeight)
		{
			return grid[indexX * gridHeight + indexY];
		}
	}
	return -1;
}

bool GridComponent::setGridElement(Vector2Int index, int element)
{
	return setGridElement(index.x, index.y, element);
}

int GridComponent::getGridElement(Vector2Int index) const
{
	return getGridElement(index.x, index.y);
}

void GridComponent::setTileTraduction(int traductionIndex, TileTraduction* traduction)
{
	tileTraduction[traductionIndex] = traduction;
}

TileTraduction* GridComponent::getTileTraduction(int traductionIndex) const
{
	if (tileTraduction.find(traductionIndex) != tileTraduction.end())
	{
		return tileTraduction.at(traductionIndex);
	}
	return new TileTraduction;
}

void GridComponent::setAstarTraduction(int traductionIndex, AstarTraduction traduction)
{
	astarTraduction[traductionIndex] = traduction;
}

AstarTraduction GridComponent::getAstarTraduction(int traductionIndex) const
{
	if (astarTraduction.find(traductionIndex) != astarTraduction.end())
	{
		return astarTraduction.at(traductionIndex);
	}
	return AstarTraduction{ false, 0, 0 };
}

AstarTraduction GridComponent::getAstarTraduction(int indexX, int indexY) const
{
	int tile = getGridElement(indexX, indexY);
	return getAstarTraduction(tile);
}

AstarTraduction GridComponent::getAstarTraduction(Vector2Int index) const
{
	return getAstarTraduction(index.x, index.y);
}

void GridComponent::setTileSize(Vector2 tileSizeP)
{
	tileSize = tileSizeP;

	resetGridRectCol();
}

bool GridComponent::intersectWithScreenPoint(Vector2 point, int* gridPosReturnX, int* gridPosReturnY)
{
	Vector2 grid_origin_screen_pos = owner.getPosition() - owner.getGame().getCamera().getCamPos();

	int tile_pos_intersection_x = Maths::floor((point.x - grid_origin_screen_pos.x) / (tileSize.x * owner.getScale()));
	int tile_pos_intersection_y = Maths::floor((point.y - grid_origin_screen_pos.y) / (tileSize.y * owner.getScale()));

	if (tile_pos_intersection_x < 0 || tile_pos_intersection_y < 0 || tile_pos_intersection_x >= gridWidth || tile_pos_intersection_y >= gridHeight)
	{
		return false;
	}

	if (gridPosReturnX) *gridPosReturnX = tile_pos_intersection_x;
	if (gridPosReturnY) *gridPosReturnY = tile_pos_intersection_y;

	int index = grid[tile_pos_intersection_x * gridHeight + tile_pos_intersection_y];
	if (tileTraduction.find(index) != tileTraduction.end())
	{
		return tileTraduction[index]->colTraduction;
	}
	return false;
}

bool GridComponent::intersectWithCircleCol(const CircleCollisionComponent& circle, int* gridPosReturnX, int* gridPosReturnY)
{
	resetGridRectCol();
	if (!gridRectCol->intersectWithCircleCollision(circle)) return false;

	Vector2 grid_origin_screen_pos = owner.getPosition() - owner.getGame().getCamera().getCamPos();
	Vector2 circle_center = circle.getCenter();
	float circle_radius = circle.getRadius();
	Vector2 up_left_corner = Vector2{ circle_center.x - circle_radius, circle_center.y - circle_radius };
	Vector2 down_right_corner = Vector2{ circle_center.x + circle_radius, circle_center.y + circle_radius };

	int tile_pos_up_left_x = Maths::floor((up_left_corner.x - grid_origin_screen_pos.x) / (tileSize.x * owner.getScale()));
	int tile_pos_up_left_y = Maths::floor((up_left_corner.y - grid_origin_screen_pos.y) / (tileSize.y * owner.getScale()));
	int tile_pos_down_right_x = Maths::floor((down_right_corner.x - grid_origin_screen_pos.x) / (tileSize.x * owner.getScale()));
	int tile_pos_down_right_y = Maths::floor((down_right_corner.y - grid_origin_screen_pos.y) / (tileSize.y * owner.getScale()));

	tile_pos_up_left_x = Maths::max(tile_pos_up_left_x, 0);
	tile_pos_up_left_y = Maths::max(tile_pos_up_left_y, 0);
	tile_pos_down_right_x = Maths::min(tile_pos_down_right_x, gridWidth - 1);
	tile_pos_down_right_y = Maths::min(tile_pos_down_right_y, gridHeight - 1);

	bool true_col_found = false;
	bool need_grid_pos_return = gridPosReturnX || gridPosReturnY;
	int nearest_true_col_sqlength = INT_MAX;

	for (int x = tile_pos_up_left_x; x <= tile_pos_down_right_x; x++)
	{
		for (int y = tile_pos_up_left_y; y <= tile_pos_down_right_y; y++)
		{
			int index = grid[x * gridHeight + y];
			if (tileTraduction.find(index) != tileTraduction.end())
			{
				if (tileTraduction[index]->colTraduction)
				{
					float xf = static_cast<float>(x) * (tileSize.x * owner.getScale());
					float yf = static_cast<float>(y) * (tileSize.y * owner.getScale());
					gridRectCol->setRectangle(Rectangle{ grid_origin_screen_pos.x + xf, grid_origin_screen_pos.y + yf, xf + (tileSize.x * owner.getScale()), yf + (tileSize.y * owner.getScale()) });
					if (!gridRectCol->intersectWithCircleCollision(circle)) continue;

					true_col_found = true;
					if (need_grid_pos_return)
					{
						Vector2 center_to_tile = Vector2{ grid_origin_screen_pos.x + ((x + 0.5f) * (tileSize.x * owner.getScale())), grid_origin_screen_pos.y + ((y + 0.5f) * (tileSize.y * owner.getScale())) } - circle_center;
						float sqlength = center_to_tile.lengthSq();
						if (sqlength < nearest_true_col_sqlength)
						{
							if (gridPosReturnX) *gridPosReturnX = x;
							if (gridPosReturnY) *gridPosReturnY = y;
							nearest_true_col_sqlength = sqlength;
						}
					}
					else
					{
						resetGridRectCol();
						return true;
					}
				}
			}
		}
	}

	resetGridRectCol();
	return true_col_found;
}

bool GridComponent::intersectWithRectangleCol(const RectangleCollisionComponent& rectangle, int* gridPosReturnX, int* gridPosReturnY)
{
	resetGridRectCol();
	if (!gridRectCol->intersectWithRectCollision(rectangle)) return false;

	Vector2 grid_origin_screen_pos = owner.getPosition() - owner.getGame().getCamera().getCamPos();
	Rectangle scaled_rect = rectangle.getTransformedRectangle();
	Vector2 rect_center = Vector2{ scaled_rect.x + (scaled_rect.width / 2.0f), scaled_rect.y + (scaled_rect.height / 2.0f) };
	Vector2 up_left_corner = Vector2{ scaled_rect.x, scaled_rect.y };
	Vector2 down_right_corner = Vector2{ scaled_rect.x + scaled_rect.width, scaled_rect.y + scaled_rect.height };

	int tile_pos_up_left_x = Maths::floor((up_left_corner.x - grid_origin_screen_pos.x) / (tileSize.x * owner.getScale()));
	int tile_pos_up_left_y = Maths::floor((up_left_corner.y - grid_origin_screen_pos.y) / (tileSize.y * owner.getScale()));
	int tile_pos_down_right_x = Maths::floor((down_right_corner.x - grid_origin_screen_pos.x) / (tileSize.x * owner.getScale()));
	int tile_pos_down_right_y = Maths::floor((down_right_corner.y - grid_origin_screen_pos.y) / (tileSize.y * owner.getScale()));

	tile_pos_up_left_x = Maths::max(tile_pos_up_left_x, 0);
	tile_pos_up_left_y = Maths::max(tile_pos_up_left_y, 0);
	tile_pos_down_right_x = Maths::min(tile_pos_down_right_x, gridWidth - 1);
	tile_pos_down_right_y = Maths::min(tile_pos_down_right_y, gridHeight - 1);

	bool true_col_found = false;
	bool need_grid_pos_return = gridPosReturnX || gridPosReturnY;
	int nearest_true_col_sqlength = INT_MAX;

	for (int x = tile_pos_up_left_x; x <= tile_pos_down_right_x; x++)
	{
		for (int y = tile_pos_up_left_y; y <= tile_pos_down_right_y; y++)
		{
			int index = grid[x * gridHeight + y];
			if (tileTraduction.find(index) != tileTraduction.end())
			{
				if (tileTraduction[index]->colTraduction)
				{
					true_col_found = true;
					if (need_grid_pos_return)
					{
						Vector2 center_to_tile = Vector2{ grid_origin_screen_pos.x + ((x + 0.5f) * (tileSize.x * owner.getScale())), grid_origin_screen_pos.y + ((y + 0.5f) * (tileSize.y * owner.getScale())) } - rect_center;
						float sqlength = center_to_tile.lengthSq();
						if (sqlength < nearest_true_col_sqlength)
						{
							if (gridPosReturnX) *gridPosReturnX = x;
							if (gridPosReturnY) *gridPosReturnY = y;
							nearest_true_col_sqlength = sqlength;
						}
					}
					else
					{
						return true;
					}
				}
			}
		}
	}

	return true_col_found;
}

bool GridComponent::screenPointAsGridCoordinates(Vector2 point, int* gridPosReturnX, int* gridPosReturnY)
{
	Vector2 cam_scaled_point = point - owner.getGame().getCamera().getCamPos();

	Vector2 grid_origin_screen_pos = owner.getPosition() - owner.getGame().getCamera().getCamPos();

	int tile_pos_intersection_x = Maths::floor((cam_scaled_point.x - grid_origin_screen_pos.x) / (tileSize.x * owner.getScale()));
	int tile_pos_intersection_y = Maths::floor((cam_scaled_point.y - grid_origin_screen_pos.y) / (tileSize.y * owner.getScale()));

	*gridPosReturnX = tile_pos_intersection_x;
	*gridPosReturnY = tile_pos_intersection_y;

	if (tile_pos_intersection_x < 0 || tile_pos_intersection_y < 0 || tile_pos_intersection_x >= gridWidth || tile_pos_intersection_y >= gridHeight)
	{
		return false;
	}

	return true;
}

void GridComponent::draw(RendererSDL& renderer)
{
	if (!willLoad) return;
	if (gridWidth <= 0 || gridHeight <= 0) return;
	if (tileSize.x <= 0 || tileSize.y <= 0) return;

	Vector2 grid_origin = owner.getPosition() - owner.getGame().getCamera().getCamPos();
	int min_x_index = Maths::max(0, 0 - Maths::ceil(grid_origin.x / (tileSize.x * owner.getScale())));
	int min_y_index = Maths::max(0, 0 - Maths::ceil(grid_origin.y / (tileSize.y * owner.getScale())));
	int max_x_index = gridWidth - Maths::floor(Maths::max(0.0f, grid_origin.x + ((tileSize.x * owner.getScale()) * gridWidth) - screenSize.x) / (tileSize.x * owner.getScale()));
	int max_y_index = gridHeight - Maths::floor(Maths::max(0.0f, grid_origin.y + ((tileSize.y * owner.getScale()) * gridHeight) - screenSize.y) / (tileSize.y * owner.getScale()));

	if (max_x_index <= 0 || max_y_index <= 0) return;

	float tile_rect_orig_y = grid_origin.y + min_y_index * (tileSize.y * owner.getScale());
	for (int y = min_y_index; y < max_y_index; y++)
	{
		float tile_rect_orig_x = grid_origin.x + min_x_index * (tileSize.x * owner.getScale());
		for (int x = min_x_index; x < max_x_index; x++)
		{
			Rectangle tile = Rectangle{ tile_rect_orig_x, tile_rect_orig_y, (tileSize.x * owner.getScale()), (tileSize.y * owner.getScale()) };
			int index = grid[x * gridHeight + y];
			if (tileTraduction.find(index) != tileTraduction.end())
			{
				tileTraduction[index]->drawTraduction->draw(renderer, tile, index);
			}

			tile_rect_orig_x += (tileSize.x * owner.getScale());
		}

		tile_rect_orig_y += (tileSize.y * owner.getScale());
	}
}

void GridComponent::debug(RendererSDL& renderer)
{
	Vector2 mouse_pos = owner.getGame().getMousePosition();

	int intersection_x, intersection_y;
	if (intersectWithScreenPoint(mouse_pos, &intersection_x, &intersection_y))
	{
		Vector2 tile_pos = owner.getPosition() - owner.getGame().getCamera().getCamPos();
		Rectangle tile = Rectangle{ tile_pos.x + (intersection_x * (tileSize.x * owner.getScale())), tile_pos.y + (intersection_y * (tileSize.y * owner.getScale())), (tileSize.x * owner.getScale()), (tileSize.y * owner.getScale()) };
		renderer.drawDebugTile(tile, Color::white);
	}
}

void GridComponent::resetGridRectCol()
{
	gridRectCol->setRectangle(Rectangle{ 0.0f, 0.0f, gridWidth * (tileSize.x * owner.getScale()), gridHeight * (tileSize.y * owner.getScale()) });
}
