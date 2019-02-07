#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Map.h"
#include <stdlib.h> // rand()

class Zombie : public Entity
{
private:
	Animation* animation = NULL;	//animation that use for this entity

	int lengthOfMovement = 10;

public:
	bool faceRight;
	int destinationRow;	//row posiont of hero in map array
	int destinationColumn; //column posiont of hero in map array

	float drawX, drawY;

	float angle;
	float movementSpeed;

	Zombie();
	~Zombie();

	void setAnimation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);	//set animateion to an entity
	
	
	//void addZomebieToScreen();

	//overriding
	virtual void update(float dt);
	virtual void draw();
	void randomDirection();
};

