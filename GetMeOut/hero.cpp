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
	//draw character based on offset of camera
	drawX = position.x - Globals::camera.x;
	drawY = position.y - Globals::camera.y;

	if (!isHeroRunFlag) 
	{
		//set destination position and size of object
		destinationRect = { (int)drawX,(int)drawY,(int)w,(int)h };

		if (!faceRight) {
			SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;
			flipType = SDL_FLIP_HORIZONTAL;
			//draw														0 - rotate angle, NULL - SDL_Point* for rotation point on image, flip flag
			SDL_RenderCopyEx(Globals::renderer, texture, NULL, &destinationRect,0,NULL,flipType);
		}
		else
		{
			//draw hero texture
			SDL_RenderCopy(Globals::renderer, texture, NULL, &destinationRect);
		}

		
	}
	else 
	{
		if (animation != NULL) {
			if (faceRight)
				animation->draw(drawX, drawY,0.13f);
			else
				animation->draw(drawX, drawY,0.13f, true);
		}
	}
	
}
