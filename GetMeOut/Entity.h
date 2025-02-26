#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"
#include "Globals.h"
#include <list>
#include <limits>
#include <algorithm>

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

	static list<Entity*> *entities;
	

	//FOR COLLISIONS
	bool bumpIntoSolids = false; //do I run into stuff?
	bool solid = false; //do things run into me?
	SDL_Rect collisionBox;
	

	Entity();
	~Entity();

	void setTexture(const char* fileName, SDL_Renderer* renderer, int optionRemoveBackground = 0, int r=255, int g=255, int b=255);	//load image to surface, then create texture from surface
	float getX(); //get position x of entity
	float getY();	//get position y of entity
	void setXY(float x, float y);	//set position X,Y for object 
	void setX(float x);	//set position x for object
	void setY(float y);//set position y for object
	void setWH(float w, float h);	//set size for object
	void setSourceRect(float x, float y, float w, float h);

	virtual void update(float dt);
	virtual void updateMovement(float dt);
	virtual void draw();
	virtual void updateCollisionBox();
	virtual void updateCollisions(float dt);

	float SweptAABB(SDL_Rect movingBox, Vector vec, SDL_Rect otherBox, float &normalX, float &normalY);
	SDL_Rect GetSweptBroadphaseBox(SDL_Rect b, Vector vec);
	bool AABBCheck(SDL_Rect b1, SDL_Rect b2);

};

