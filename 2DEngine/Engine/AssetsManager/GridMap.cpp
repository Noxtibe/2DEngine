#include "GridMap.h"
#include "../Utilitaire/Log.h"
#include <fstream>
#include <iostream>

GridMap::GridMap(string pathP, int mapWidthP, int mapHeightP, vector<int> gridMapP) : path(pathP), mapWidth(mapWidthP), mapHeight(mapHeightP), gridMap(gridMapP)
{
}

GridMap* GridMap::load(const string& pathP)
{
	vector<int> grid_map;
	int grid_map_width = 0;
	int grid_map_height = 0;

	std::ifstream file;
	file.open(pathP);
	string line;
	if (file.is_open())
	{
		bool data_reading = false;
		int data_lines_read = 0;
		while (file)
		{
			std::getline(file, line);

			if (data_reading)
			{
				if (data_lines_read >= grid_map_height)
				{
					data_reading = false;
					break;
				}
				else
				{
					string values = line.erase(0, 8);
					for (int i = 0; i < grid_map_width; i++)
					{
						string value = values;
						int chars_to_keep = 0;
						for (auto iter : value)
						{
							if (iter == ',') break;
							chars_to_keep++;
						}
						value.erase(value.begin() + chars_to_keep, value.end());
						grid_map.push_back(std::stoi(value));
						values.erase(0, 2 + chars_to_keep);
					}

					data_lines_read++;
				}
			}

			if (grid_map_width == 0)
			{
				std::size_t found = line.find("width");
				if (found != std::string::npos)
				{
					string value = line.erase(0, 10);
					value.pop_back();
					grid_map_width = std::stoi(value);
				}
			}
			else if (grid_map_height == 0)
			{
				std::size_t found = line.find("height");
				if (found != std::string::npos)
				{
					string value = line.erase(0, 11);
					value.pop_back();
					grid_map_height = std::stoi(value);
				}
			}
			else
			{
				std::size_t found = line.find("data");
				if (found != std::string::npos)
				{
					data_reading = true;
				}
			}
		}
		if (grid_map_width == 0 || grid_map_height == 0)
		{
			Log::error(LogCategory::Application, "File " + pathP + " doesn't contain needed informations");
			return nullptr;
		}
	}
	else
	{
		Log::error(LogCategory::Application, "Couldn't open file " + pathP);
		return nullptr;
	}

	Log::info("Loaded grid map " + pathP);
	return new GridMap(pathP, grid_map_width, grid_map_height, grid_map);
}
