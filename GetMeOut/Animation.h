#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Animation
{
public:

	//basic info
	int numberOfFrames;	//number of sprite sheet frame
	int frameWidth, frameHeight;	//width and height of frame that we need to load from sprite sheet
	float frameDuration; //how long does from last on screen. this small number equal quick movement.
	SDL_Texture* spriteSheet; //point to existing texture
	SDL_Renderer* renderer;		//use to draw to the window
	int r, g, b; //reference to rgb colour. use to remove backgroud from animation. r=red, b=blue, g=green

	//currnet state of the animation
	int currentFrame;	//which frame to show
	float frameTimer;	//how long has the current frame been on screen so far

	//when create new object, load sprite sheet to object                                                                             rgb color reference to remove background
	Animation(const char* fileName, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration, int optionRemoveBackground, int r=255, int g=255, int b=255);


	void update(float dt);
	void draw(int x, int y);	//draw object
	void draw(int x, int y, float scale);	//draw object and use scale to manage object size
	void draw(int x, int y, bool flip);	//draw object by flip to another direction
	void draw(int x, int y, float scale, bool flip);	//draw object by flip to another direction and set scale to manage object size

};

