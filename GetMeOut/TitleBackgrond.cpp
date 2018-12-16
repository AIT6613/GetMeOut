#include "TitleBackgrond.h"



TitleBackgrond::TitleBackgrond()
{
	w = 800;
	h = 600;
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	//draw rectangle
	SDL_RenderFillRect(renderer, &titleBackgroundRect);
}