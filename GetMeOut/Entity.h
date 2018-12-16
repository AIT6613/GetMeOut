#pragma once
#include <SDL.h>
#include "Vector.h"

class Entity
{

protected:
	SDL_Renderer* renderer;

public:
	Vector position; //position
	Vector velocity; //how fast and which way to move this thing

	Entity();
	~Entity();

	void setRenderer(SDL_Renderer* renderer);
	void setXY(float x, float y);
	void setX(float x);
	void setY(float y);

	virtual void update(float dt);
	virtual void updateMovement(float dt);
	virtual void draw();
};

