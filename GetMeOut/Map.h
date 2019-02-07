#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Map
{
private:
	

public:
	int row, column, freeSpaceCount = 0;
	int** map;
	int** freeSpace;

	int blockWidth, blockHeight; //size of one block in map


	Map();
	~Map();

	void setArrayBlockSize(int blockWidth, int blockHeight);
	void loadMapFromFile(const char* filePath);

};

