#include "Animation.h"

Animation::Animation(const char * fileName, SDL_Renderer * renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration, int optionRemoveBackground, int r, int g, int b)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	//set background of sprite to be transparent
	//params: surface to change
	//		1 = turn on,  0 = turn off
	//		which colour to user as colour key (SDL_MapRGB will find closest colour match in the surface to set it to)
	SDL_SetColorKey(tempSurface, optionRemoveBackground, SDL_MapRGB(tempSurface->format, r, g, b));

	//convert surface to texture
	this->spriteSheet = SDL_CreateTextureFromSurface(renderer, tempSurface);

	//free up its memory
	SDL_FreeSurface(tempSurface);

	this->renderer = renderer;
	this->numberOfFrames = numberOfFrames;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->frameDuration = frameDuration;

	currentFrame = 0;
	frameTimer = 0;

}

void Animation::update(float dt)
{
	//update the frameTimer
	frameTimer += dt;

	//if thsi time exceeds duration, move onto next frame
	if (frameTimer >= frameDuration) {
		currentFrame++;

		//reset the timer
		frameTimer = 0;

		if (currentFrame >= numberOfFrames) {
			//loop back to start frame
			currentFrame = 0;
			//ELSE
			//trigger end of animation code or something

		}
	}
}

void Animation::draw(int x, int y)
{
	SDL_Rect sourceRect;
	sourceRect.x = currentFrame * frameWidth;	//e.g currentFrame 2, frameWidth 32, x source is 64
	sourceRect.y = 0;
	sourceRect.w = frameWidth;
	sourceRect.h = frameHeight;

	//destination to draw
	SDL_Rect dest = { x,y, frameWidth,frameHeight };
	//draw
	SDL_RenderCopy(renderer, spriteSheet, &sourceRect, &dest);
}


void Animation::draw(int x, int y, float scale)
{
	SDL_Rect sourceRect;
	sourceRect.x = currentFrame * frameWidth;	//e.g currentFrame 2, frameWidth 32, x source is 64
	sourceRect.y = 0;
	sourceRect.w = frameWidth;
	sourceRect.h = frameHeight;

	//destination to draw with the scale of object size
	SDL_Rect dest = { x,y, frameWidth*scale,frameHeight*scale };
	//draw
	SDL_RenderCopy(renderer, spriteSheet, &sourceRect, &dest);
}


void Animation::draw(int x, int y, bool flip)
{
	SDL_Rect sourceRect;
	sourceRect.x = currentFrame * frameWidth;	//e.g currentFrame 2, frameWidth 32, x source is 64
	sourceRect.y = 0;
	sourceRect.w = frameWidth;
	sourceRect.h = frameHeight;

	//destination, where do we want to draw
	SDL_Rect dest = { x,y, frameWidth,frameHeight };

	//get the correct flip flag
	SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;
	if (flip)
		flipType = SDL_FLIP_HORIZONTAL;

	//draw														0 - rotate angle, NULL - SDL_Point* for rotation point on image, flip flag
	SDL_RenderCopyEx(renderer, spriteSheet, &sourceRect, &dest, 0, NULL, flipType);
};

void Animation::draw(int x, int y, float scale, bool flip)
{
	SDL_Rect sourceRect;
	sourceRect.x = currentFrame * frameWidth;	//e.g currentFrame 2, frameWidth 32, x source is 64
	sourceRect.y = 0;
	sourceRect.w = frameWidth;
	sourceRect.h = frameHeight;

	// destination to draw with the scale of object size
	SDL_Rect dest = { x,y, frameWidth*scale,frameHeight*scale };

	//get the correct flip flag
	SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;
	if (flip)
		flipType = SDL_FLIP_HORIZONTAL;

	//draw														0 - rotate angle, NULL - SDL_Point* for rotation point on image, flip flag
	SDL_RenderCopyEx(renderer, spriteSheet, &sourceRect, &dest, 0, NULL, flipType);
};