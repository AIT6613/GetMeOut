#pragma once
#include <SDL.h>
#include "Vector.h"

class Entity
{

protected:
	//basic info we need
	//int frameWidth, frameHeight;
	SDL_Texture* texture; //point to existing texture somewhere (we wont load it up here)
	SDL_Renderer* renderer;		//need this guy to draw to the window
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

public:
	Vector position; //position
	Vector velocity; //how fast and which way to move this thing

	Entity();
	~Entity();

	void setRenderer(SDL_Renderer* renderer);
	void setTexture(SDL_Texture* texture, SDL_Rect sourecRect, SDL_Rect deatinationRect);
	void setXY(float x, float y);
	void setX(float x);
	void setY(float y);

	virtual void update(float dt);
	virtual void updateMovement(float dt);
	virtual void draw();
};

