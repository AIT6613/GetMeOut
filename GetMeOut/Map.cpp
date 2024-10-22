#include "Map.h"

Map::Map()
{

}


Map::~Map()
{
}

void Map::setArrayBlockSize(int blockWidth, int blockHeight)
{
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
}

void Map::loadMapFromFile(const char * filePath)
{
	string textString;
	
	//Read map file
	ifstream mapFile(filePath);

	//1 line is column number
	getline(mapFile, textString);
	column = atoi(textString.c_str());
	char* textChar = new char[column];

	//2 line is row number
	getline(mapFile, textString);
	row = atoi(textString.c_str());

	//all the rest is map e.g. 0 = land, 1 = wall (dead zone)
	//create new row for array
	map = new int*[row];
	for (int i = 0; i < row; ++i)
		//crate new column for array
		map[i] = new int[column];

	for (int i = 0; i < row; i++) {
		//read map from file and install to map array
		//get string line from file
		getline(mapFile, textString);
		//covert string to char array
		strcpy_s(textChar, column+1, textString.c_str());
		for (int j = 0; j < column; j++) {
			//put char array to map array
			map[i][j] = textChar[j]-48;

			if (map[i][j] == 0)
			{
				//count free space for create array
				freeSpaceRows++;
			}
		}

	}


	freeSpace = new int*[freeSpaceRows];
	for (int i = 0; i < freeSpaceRows; ++i)
		//crate new column for array
		freeSpace[i] = new int[2];
	//create free space array
	int r = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (map[i][j] == 0)
			{
				//count free space for create array
				freeSpace[r][0] = i;
				freeSpace[r][1] = j;

				r++;
			}
		}

	}
}





