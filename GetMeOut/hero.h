#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Map.h"
#include "Zombie.h"
#include "Globals.h"

class Hero : public Entity
{
private:
	Animation* animation = NULL;	//animation that use for this entity

public:
	bool isHeroRunFlag = false; //use to indicate hero on running action or idle
	bool faceRight;
	int destinationRow;	//row posiont of hero in map array
	int destinationColumn; //column posiont of hero in map array

	float drawX, drawY;

	bool isWin; //use to indicate player win or not

	Hero();
	~Hero();

	void setAnimation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);	//set animateion to an entity

	void checkWinStatus(int destinationRow, int destinationColumn);

	//overriding
	virtual void update(float dt);
	virtual void draw();
	virtual void updateCollisions(float dt);
	

	// TODO: check colision between hero and zombie
	// if colision, decrease HP
	// if HP < 0, hero die
	// update topRank file 


	// TODO: check colision between hero and curl item
	// if yes, hero get increase HP



};

