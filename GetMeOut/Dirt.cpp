#include "Dirt.h"



Dirt::Dirt()
{
}


Dirt::~Dirt()
{
}

void Dirt::draw()
{
	//set destination position and size of object
	SDL_Rect destinationRect = { position.x,position.y,w,h };

	//draw title background
	SDL_RenderCopy(renderer, texture, &sourceRect, &destinationRect);
}
