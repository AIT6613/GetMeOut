#include "Zombie.h"

Zombie::Zombie(void)
{
	animation = NULL;
	faceRight = true;

	
}


Zombie::~Zombie(void)
{
}

void Zombie::setAnimation(Animation* animation)
{
	this->animation = animation;
}

void Zombie::update(float dt)
{
	randomDirection();

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
	movementSpeed = 100;

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


	//check held keys and update velocity
	if (velocity.y > 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = (((int)position.y + (int)h - lengthOfMovement) / Globals::mazeMap->blockHeight);
		destinationColumn = ((int)position.x + (int)w) / Globals::mazeMap->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
		{
			//move hero up
			velocity.y += (velocity.y * 2);
		}

	}
	else if (velocity.y < 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = (((int)position.y + (int)h + lengthOfMovement) / Globals::mazeMap->blockHeight);
		destinationColumn = ((int)position.x + (int)w) / Globals::mazeMap->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
		{
			//move hero down
			velocity.y -= (velocity.y * 2);
		}

	}
	else if (velocity.x > 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = ((int)position.y + (int)h) / Globals::mazeMap->blockHeight;
		destinationColumn = (((int)position.x) - lengthOfMovement) / Globals::mazeMap->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
		{
			//move hero to the left
			velocity.x += (velocity.x * 2);
		}

	}
	else if (velocity.x < 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = ((int)position.y + (int)h) / Globals::mazeMap->blockHeight;
		destinationColumn = (((int)position.x) + (int)w + lengthOfMovement) / Globals::mazeMap->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
		{
			//move hero to the right
			velocity.x -= (velocity.x * 2);
		}


	}
	
}
