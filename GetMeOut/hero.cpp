#include "Hero.h"



Hero::Hero(void)
{
	animation = NULL;
	faceRight = true;
}


Hero::~Hero(void)
{
}

void Hero::setAnimation(Animation* animation)
{
	this->animation = animation;
}

void Hero::update(float dt)
{
	/*
	//movement
	if (faceRight)
		velocity.x = 150;
	else
		velocity.x = -150;

	if (position.x > 800)
		faceRight = false;
	else if (position.x <= 0)
		faceRight = true;
	*/

	if (velocity.x > 0)
		faceRight = true;
	if (velocity.x < 0)
		faceRight = false;

	//move character based on velocity
	updateMovement(dt);

	//update animation
	animation->update(dt);
}

void Hero::draw()
{
	if (animation != NULL) {
		if (faceRight)
			animation->draw(position.x, position.y, 0.25f);
		else
			animation->draw(position.x, position.y, 0.25f, true);
	}
}
