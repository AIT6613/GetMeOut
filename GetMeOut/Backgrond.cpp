#include "Backgrond.h"



Backgrond::Backgrond()
{
}


Backgrond::~Backgrond()
{

}

void Backgrond::draw()
{
	
	SDL_Rect destinationRect = { position.x,position.y,w,h };

	//draw title background
	SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
}