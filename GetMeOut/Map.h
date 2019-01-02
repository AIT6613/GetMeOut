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

	Map();
	~Map();

	void loadMapFromFile(const char* filePath);
	void mapPrintTest();

};

