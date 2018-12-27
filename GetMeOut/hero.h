#pragma once
#include "Entity.h"
#include "Animation.h"

class Hero : public Entity
{
private:
	Animation* animation = NULL;	//animation that use for this entity
	bool faceRight;



public:
	Hero();
	~Hero();

	void setAnimation(Animation* animation);	//set animateion to an entity

	//overriding
	virtual void update(float dt);
	virtual void draw();
};

