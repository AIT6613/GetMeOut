#include "KeyboardHandler.h"



KeyboardHandler::KeyboardHandler()
{
}


KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::update(SDL_Event* event) {

}


void KeyboardHandler::updateHeldKeys(Map* map) {
	//get array of all keyboard key states (1 = hel down, 0 = not held down)
	const Uint8* keystates = SDL_GetKeyboardState(NULL); //param: array of ints to indicate which keys we want states about or NULL for all

	//reset velocity for hero to nothng 
	hero->velocity.x = 0;
	hero->velocity.y = 0;


	//TODO:
	//cheek hero position compare with map
	//if hero need to go some where, there should not be dead zone
	
	

	//check held keys and update velocity
	if (keystates[SDL_SCANCODE_UP])
	{
		//caluculate destination row and colum
		                                                                    //size of block
		hero->destinationRow = (((int)hero->position.y + (int)hero->h - lengthOfMovement) / map->blockHeight);
		hero->destinationColumn = ((int)hero->position.x + (int)hero->w) / map->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (map->map[hero->destinationRow][hero->destinationColumn] == 0)
		{
			//set hero action to running
			hero->isHeroRunFlag = true;
			//move hero up
			hero->velocity.y = -500;
		}

	} 
	else if (keystates[SDL_SCANCODE_DOWN])
	{
		//caluculate destination row and colum
																			//size of block
		hero->destinationRow = (((int)hero->position.y + (int)hero->h + lengthOfMovement) / map->blockHeight);
		hero->destinationColumn = ((int)hero->position.x + (int)hero->w) / map->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (map->map[hero->destinationRow][hero->destinationColumn] == 0)
		{
			//set hero action to running
			hero->isHeroRunFlag = true;
			//move hero down
			hero->velocity.y = 500;
		}

	} 
	else if (keystates[SDL_SCANCODE_LEFT])
	{
		//caluculate destination row and colum
																			//size of block
		hero->destinationRow = ((int)hero->position.y + (int)hero->h) / map->blockHeight;
		hero->destinationColumn = (((int)hero->position.x) - lengthOfMovement) / map->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (map->map[hero->destinationRow][hero->destinationColumn] == 0)
		{
			//set hero action to running
			hero->isHeroRunFlag = true;
			//move hero to the left
			hero->velocity.x = -500;
		}
		
	} 
	else if (keystates[SDL_SCANCODE_RIGHT])
	{
		//caluculate destination row and colum
																			//size of block
		hero->destinationRow = ((int)hero->position.y + (int)hero->h) / map->blockHeight;
		hero->destinationColumn = (((int)hero->position.x) + (int)hero->w + lengthOfMovement) / map->blockHeight;
		//check destination position is dezone or not
		//if not, move hero
		if (map->map[hero->destinationRow][hero->destinationColumn] == 0)
		{
			//set hero action to running
			hero->isHeroRunFlag = true;
			//move hero to the right
			hero->velocity.x = 500;
		}

		
	}
	else
	{
		//set hero action to idle
		hero->isHeroRunFlag = false;
	}

		

}

