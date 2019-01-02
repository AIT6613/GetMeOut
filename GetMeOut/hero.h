#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Map.h"

class Hero : public Entity
{
private:
	Animation* animation = NULL;	//animation that use for this entity

public:
	bool isHeroRunFlag = false; //use to indicate hero on running action or idle
	bool faceRight;
	int destinationRow;	//row posiont of hero in map array
	int destinationColumn; //column posiont of hero in map array

	Hero();
	~Hero();

	void setAnimation(Animation* animation);	//set animateion to an entity

	//overriding
	virtual void update(float dt);
	virtual void draw();
};

