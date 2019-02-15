#include "Zombie.h"

Zombie::Zombie(void)
{
	animation = NULL;
	faceRight = true;

	
}


Zombie::~Zombie(void)
{
}

void Zombie::setAnimation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration)
{
	this->animation = new Animation(spriteSheet, renderer, numberOfFrames, frameWidth, frameHeight, frameDuration);
}



void Zombie::update(float dt)
{
	//before we move our beloved hero, we'll see if they crash into anything on their predicted path
	updateCollisions(dt);


	//try to random direction
	randomDirection();
	//velocity.y = 800;

	//zombie move up
	if (velocity.y<0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = (((int)position.y + (int)h - 20) / Globals::mazeMap->blockHeight);
		destinationColumn = ((int)position.x + (int)w) / Globals::mazeMap->blockHeight;

		if (destinationRow < 0)
			destinationRow = 0;
		if (destinationColumn < 0)
			destinationColumn = 0;

		//check destination position is dezone or not
		//if not, move zombie
		try
		{
			if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
			{
				//make zomebie move to another direction
				velocity.y = velocity.y - (velocity.y * 2);
			}
		}
		catch (exception ex)
		{

		}
		

	}
	//zombie move down
	if (velocity.y > 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = (((int)position.y + (int)h + lengthOfMovement) / Globals::mazeMap->blockHeight);
		destinationColumn = ((int)position.x + (int)w) / Globals::mazeMap->blockHeight;

		if (destinationRow < 0)
			destinationRow = 0;
		if (destinationColumn < 0)
			destinationColumn = 0;

		try
		{
			//check destination position is dezone or not
		//if it is dead zone, move zombie to another way
			if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
			{
				//make zomebie move to another direction
				velocity.y = velocity.y - (velocity.y * 2);
			}
		}
		catch (const std::exception&)
		{

		}
		

	}
	
	//Zombie move left
	if (velocity.x < 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = ((int)position.y + (int)h) / Globals::mazeMap->blockHeight;
		destinationColumn = (((int)position.x) - lengthOfMovement) / Globals::mazeMap->blockHeight;

		if (destinationRow < 0)
			destinationRow = 0;
		if (destinationColumn < 0)
			destinationColumn = 0;

		try
		{
			//check destination position is dezone or not
		//if it is dead zone, move zombie to another way
			if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
			{
				//make zomebie move to another direction
				velocity.x = velocity.x - (velocity.x * 2);
			}

		}
		catch (const std::exception&)
		{

		}
		
	}

	//zomebie move right
	if (velocity.x > 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = ((int)position.y + (int)h) / Globals::mazeMap->blockHeight;
		destinationColumn = (((int)position.x) + (int)w + lengthOfMovement) / Globals::mazeMap->blockHeight;

		if (destinationRow < 0)
			destinationRow = 0;
		if (destinationColumn < 0)
			destinationColumn = 0;

		try
		{
			//check destination position is dezone or not
		//if it is dead zone, move zombie to another way
			if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
			{
				//make zomebie move to another direction
				velocity.x = velocity.x - (velocity.x * 2);
			}
		}
		catch (const std::exception&)
		{

		}
		


	}




	if (velocity.x < 0)
		faceRight = true;
	if (velocity.x > 0)
		faceRight = false;


	

	//move character based on velocity
	updateMovement(dt);

	//update animation
	animation->update(dt);
}

void Zombie::draw()
{
	//draw character based on offset of camera
	drawX = position.x - Globals::camera.x;
	drawY = position.y - Globals::camera.y;

	if (animation != NULL) {
		if (faceRight)
			animation->draw(drawX, drawY, 0.25f);
		else
			animation->draw(drawX, drawY, 0.25f, true);
	}


}

void Zombie::randomDirection()
{
	//Zombie movement
	//set move ment speed
	movementSpeed = Globals::zomebieSpeed;

	
	//random 80% to change direction
	if ((rand() % 1000) > 995) 
	{
		
		//random angle
		angle = rand() % 360;
		//convert angle in degrees to radians
		float angleInRadians = angle / 180 * M_PI;

		velocity.x = movementSpeed * cos(angleInRadians);
		velocity.y = movementSpeed * sin(angleInRadians);
		
	}
	
}

void Zombie::updateCollisions(float dt)
{
	//make sure collisionBox is set to the right position before working out all sorts of maths
	updateCollisionBox();
}
