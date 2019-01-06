#include "Wall.h"



Wall::Wall()
{
}


Wall::~Wall()
{

}

void Wall::draw()
{

	//set destination position and size of object
	SDL_Rect destinationRect = { position.x,position.y,w,h };

	//draw title background
	SDL_RenderCopy(Globals::renderer, texture, &sourceRect, &destinationRect);
}


