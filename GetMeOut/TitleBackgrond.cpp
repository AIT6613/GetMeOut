#include "TitleBackgrond.h"



TitleBackgrond::TitleBackgrond()
{
}


TitleBackgrond::~TitleBackgrond()
{

}

void TitleBackgrond::setWH(float w, float h)
{
	this->w = w;
	this->h = h;
}

void TitleBackgrond::draw()
{
	SDL_Rect titleBackgroundRect = { position.x,position.y,w,h };

	//set draw colour
	//SDL_SetRenderDrawColor(renderer, 13,45, 66, 0);

	//draw rectangle 
	//SDL_RenderFillRect(renderer, &titleBackgroundRect);

	//draw title background
	SDL_RenderCopy(renderer, texture, &sourceRect, &destinationRect);
}