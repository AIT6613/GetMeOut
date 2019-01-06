#include "Dirt.h"



Dirt::Dirt()
{
}


Dirt::~Dirt()
{
}

void Dirt::draw()
{
	//draw map by loop array map
	//loop row of array; x
	for (int i = 0; i < Globals::mazeMap->row; i++)
	{
		//loop column of array; y
		for (int j = 0; j < Globals::mazeMap->column; j++)
		{
			try
			{
				//check if array is not dead zone
				if (Globals::mazeMap->map[i][j] == 0)
				{
					//calculate position
					drawX = (j * Globals::mazeMap->blockWidth) - Globals::camera.x;
					drawY = (i * Globals::mazeMap->blockHeight) - Globals::camera.y;

				}

				//set destination position and size of object
				destinationRect = { (int)drawX, (int)drawY ,(int)w,(int)h };

				//draw wall into map
				SDL_RenderCopy(Globals::renderer, texture, &sourceRect, &destinationRect);
			}
			catch (exception ex)
			{
				cout << "Error: " << endl;
			}

		}
	}
}
