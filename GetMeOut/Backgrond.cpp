#include "Backgrond.h"



Backgrond::Backgrond()
{
}


Backgrond::~Backgrond()
{

}

void Backgrond::draw()
{
	//set destination position and size of object
	SDL_Rect destinationRect = { position.x,position.y,w,h };

	//draw background
	SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
}