#include "Heal.h"

Heal::Heal(void)
{

}


Heal::~Heal(void)
{

}

void Heal::update(float dt)
{
	
}

void Heal::draw()
{
	//draw character based on offset of camera
	drawX = position.x - Globals::camera.x;
	drawY = position.y - Globals::camera.y;

	//set destination position and size of object
	destinationRect = { (int)drawX, (int)drawY ,(int)w,(int)h };

	//draw wall into map
	SDL_RenderCopy(Globals::renderer, texture, &sourceRect, &destinationRect);


}
