#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Map
{
private:
	

public:
	int row, column;
	int** map;

	int blockWidth, blockHeight; //size of one block in map


	Map(int blockWidth, int blockHeight);
	~Map();

	void loadMapFromFile(const char* filePath);

};

