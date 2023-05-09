#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class GridMap
{

public:

	GridMap(string pathP, int mapWidthP, int mapHeightP, vector<int> gridMapP);
	GridMap() = default;
	static GridMap* load(const string& pathP);

	string getPath() const { return path; }
	int getWidth() const { return mapWidth; }
	int getHeight() const { return mapHeight; }
	vector<int> getMap() const { return gridMap; }

private:

	string path{ "" };
	int mapWidth{ 0 };
	int mapHeight{ 0 };
	vector<int> gridMap;
};

