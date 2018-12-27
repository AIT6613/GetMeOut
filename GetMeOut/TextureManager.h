#pragma once
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:

	//basic info we need
	int frameWidth, frameHeight;
	SDL_Texture* texture; //point to existing texture somewhere (we wont load it up here)
	SDL_Renderer* renderer;		//need this guy to draw to the window

	TextureManager(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int frameWidth, int frameHeight);
	void update(float dt);
	void draw(int x, int y);
	void draw(int x, int y, float scale);
	void draw(int x, int y, bool flip);
	void draw(int x, int y, float scale, bool flip);
};

