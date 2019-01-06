#include "Wall.h"



Wall::Wall()
{
	//load image up as surface
	SDL_Surface* tempSurface = IMG_Load("assets/Wall.png");

	//next, convert to texture 
	this->texture = SDL_CreateTextureFromSurface(Globals::renderer, tempSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(tempSurface);
}


Wall::~Wall()
{

}

void Wall::draw()
{
	//draw map by loop array map
	//loop row of array; y
	for (int i = 0; i < Globals::mazeMap->row; i++)
	{
		//loop column of array; x
		for (int j = 0; j < Globals::mazeMap->column; j++)
		{
			try
			{
				//check if array is dead zone
				if (Globals::mazeMap->map[i][j] == 1)
				{
					//calculate position
					drawX = (j * Globals::mazeMap->blockWidth) - Globals::camera.x;
					drawY = (i * Globals::mazeMap->blockHeight) - Globals::camera.y;


					if (i + 1 < Globals::mazeMap->row)
					{
						//check if array under current array is dead zone
						if (Globals::mazeMap->map[i + 1][j] == 1)
							//choose wall 1; regular wall
							sourceRect = { 0,0,500,500 };
						else
							//choose wall 2, 3D wall
							sourceRect = { 500,0,500,500 };
					}
					else {
						//choose wall 1; regular wall
						sourceRect = { 0,0,500,500 };
					}


					//set destination position and size of object
					destinationRect = { (int)drawX, (int)drawY ,(int)w,(int)h };

					//draw wall into map
					SDL_RenderCopy(Globals::renderer, texture, &sourceRect, &destinationRect);
				}
			}
			catch (exception ex)
			{
				cout << "Error: "<< endl;
			}

		}
	}

	
}


