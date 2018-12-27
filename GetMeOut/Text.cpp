#include "Text.h"



Text::Text()
{
}


Text::~Text()
{
}


void Text::draw()
{
	//set destination position and size of object
	SDL_Rect destinationRect = { position.x,position.y,w,h };

	//draw title background
	SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
}