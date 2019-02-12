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

/*
void Zombie::addZomebieToScreen()
{
	// TODO: try to add zombie as same as add bullet to hero in the class
	//Loading up a png into a texture
	SDL_Surface* zombieSurface = IMG_Load("assets/Zombie.png");

	SDL_SetColorKey(zombieSurface, 1, SDL_MapRGB(zombieSurface->format, 210, 10, 190));

	//convert surface to texture
	SDL_Texture* zomebieSpriteSheet = SDL_CreateTextureFromSurface(Globals::renderer, zombieSurface); //=IMG_LoadTexture
	//zombieAnimation = new Animation(runSpriteSheet, Globals::renderer, 10, 310, 400, 0.16);	//0.2 = 200ms per frame duration

	Zombie *zombie = new Zombie();
	zombie->setAnimation(zomebieSpriteSheet, Globals::renderer, 10, 310, 400, 0.16);
	zombie->setWH(90, 90);
	zombie->setXY(600, 600);


	//add to list of entities
	Entity::entities->push_back(zombie);
}
*/


void Zombie::update(float dt)
{
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
		//check destination position is dezone or not
		//if it is dead zone, move zombie to another way
		if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
		{
			//make zomebie move to another direction
			velocity.y = velocity.y - (velocity.y*2);
		}

	}
	
	//Zombie move left
	if (velocity.x < 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = ((int)position.y + (int)h) / Globals::mazeMap->blockHeight;
		destinationColumn = (((int)position.x) - lengthOfMovement) / Globals::mazeMap->blockHeight;
		//check destination position is dezone or not
		//if it is dead zone, move zombie to another way
		if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
		{
			//make zomebie move to another direction
			velocity.x = velocity.x - (velocity.x * 2);
		}

	}

	//zomebie move right
	if (velocity.x > 0)
	{
		//caluculate destination row and colum
																			//size of block
		destinationRow = ((int)position.y + (int)h) / Globals::mazeMap->blockHeight;
		destinationColumn = (((int)position.x) + (int)w + lengthOfMovement) / Globals::mazeMap->blockHeight;
		//check destination position is dezone or not
		//if it is dead zone, move zombie to another way
		if (Globals::mazeMap->map[destinationRow][destinationColumn] == 1)
		{
			//make zomebie move to another direction
			velocity.x = velocity.x - (velocity.x * 2);
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
	
}
