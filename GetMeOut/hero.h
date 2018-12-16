#pragma once
#include "Entity.h"
#include "Animation.h"

class Hero : public Entity
{
private:
	Animation* animation = NULL;
	bool faceRight;



public:
	Hero();
	~Hero();

	void setAnimation(Animation* animation);

	//overriding
	virtual void update(float dt);
	virtual void draw();
};

