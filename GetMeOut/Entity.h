#pragma once
#include <SDL.h>
#include <SDL_image.h>
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
	float w, h;	//size of object, w = width, h = height
	

	Entity();
	~Entity();

	void setTexture(const char* fileName, SDL_Renderer* renderer);	//load image to surface, then create texture from surface
	void setXY(float x, float y);	//set position X,Y for object 
	void setX(float x);	//set position x for object
	void setY(float y);//set position y for object
	void setWH(float w, float h);	//set size for object

	virtual void update(float dt);
	virtual void updateMovement(float dt);
	virtual void draw();
};

