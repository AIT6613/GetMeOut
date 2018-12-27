#include "TextureManager.h"


TextureManager::TextureManager(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int frameWidth, int frameHeight)
{
	this->texture = spriteSheet;
	this->renderer = renderer;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;

}


void TextureManager::draw(int x, int y)
{
	SDL_Rect sourceRect;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = frameWidth;
	sourceRect.h = frameHeight;

	//destination, where do we want to draw this guy/gal
	SDL_Rect dest = { x,y, frameWidth,frameHeight };
	//draw
	SDL_RenderCopy(renderer, texture, &sourceRect, &dest);
}