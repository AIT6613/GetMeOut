#include "Hero.h"

Hero::Hero(void)
{
	animation = NULL;
	faceRight = true;

	bumpIntoSolids = true;
}


Hero::~Hero(void)
{
}


void Hero::setAnimation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration)
{
	this->animation = new Animation(spriteSheet, renderer, numberOfFrames, frameWidth, frameHeight, frameDuration);
}

void Hero::checkWinStatus(int destinationRow, int destinationColumn)
{
	if (destinationRow < 0 || destinationColumn < 0)
		isWin = true;
}


void Hero::update(float dt)
{


	if (velocity.x > 0)
		faceRight = true;
	if (velocity.x < 0)
		faceRight = false;

	//before we move our beloved hero, we'll see if they crash into anything on their predicted path
	updateCollisions(dt);

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
				animation->draw(drawX, drawY,0.21f);
			else
				animation->draw(drawX, drawY,0.21f, true);
		}
	}
	
}

void Hero::updateCollisions(float dt)
{
	//make sure collisionBox is set to the right position before working out all sorts of maths
	updateCollisionBox();

	if (entities != NULL && bumpIntoSolids && (velocity.x != 0 || velocity.y != 0))
	{
		//collision time, 0 is immediately, 1 is not at all. We want to find out where on this boxes movement path where it crashes
		float collisionTime = 1;
		//these are to help work out which side we are hitting an object on
		float normalx, normaly;
		//we only want to compare velocity based on this times movement
		Vector velocityXdt(velocity.x*dt, velocity.y*dt);

		SDL_Rect broadphasebox = GetSweptBroadphaseBox(collisionBox, velocity);

		// TODO: Loop zombie list, or Loop all but select only zombie, Let see!
		//loop through entire list to see if we hit anyone
		for (list<Entity*>::iterator e = entities->begin(); e != entities->end(); e++) {
			//if ((*e) == this || !(*e)->solid || !AABBCheck(broadphasebox, (*e)->collisionBox))
			if ((*e) == this || !AABBCheck(broadphasebox, (*e)->collisionBox))
				continue;

			//check to see if we actually collide. If we do, then tmpCollisionTime will be < 1
			float tmpNormalx, tmpNormaly;
			float tmpCollisionTime = SweptAABB(collisionBox, velocityXdt, (*e)->collisionBox, tmpNormalx, tmpNormaly);

			//is this collision closer then the last?
			if (tmpCollisionTime < collisionTime)
			{
				collisionTime = tmpCollisionTime;
				normalx = tmpNormalx;
				normaly = tmpNormaly;
			}
		}
		//after the loop

		// TODO: Decrease HP, instead of all action
		//if there was a collision, lets setup sliding to the new position instead
		if (collisionTime < 1.0f) {
			
			cout << "Hit zombie" << endl;
			
			//set minimum HP equal to zero
			if ((Globals::heroHealPoint - Globals::damagePoint) > 0)
				Globals::heroHealPoint -= Globals::damagePoint;
			else
				Globals::heroHealPoint = 0;
		}

	}
}
