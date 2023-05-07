#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Grid
{

public:

	Grid(string pathP, int mapWidthP, int mapHeightP, vector<int> GridP);
	Grid() = default;
	static Grid* load(const string& pathP);

	string getPath() const { return path; }
	int getWidth() const { return mapWidth; }
	int getHeight() const { return mapHeight; }
	vector<int> getMap() const { return GridMap; }

private:

	string path{ "" };
	int mapWidth{ 0 };
	int mapHeight{ 0 };
	vector<int> GridMap;
};