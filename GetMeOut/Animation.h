#pragma once
#include <SDL.h>


class Animation
{
public:

	//basic info we need
	int numberOfFrames;
	int frameWidth, frameHeight;
	float frameDuration; //how long does frome last on screen
	SDL_Texture* spriteSheet; //point to existing texture somewhere (we wont load it up here)
	SDL_Renderer* renderer;		//need this guy to draw to the window

	//currnet state of the animation
	int currentFrame;	//which frame to show
	float frameTimer;	//how long has the current frame been on screen so far

	Animation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);
	void update(float dt);
	void draw(int x, int y);
	void draw(int x, int y, float scale);
	void draw(int x, int y, bool flip);
	void draw(int x, int y, float scale, bool flip);

};

