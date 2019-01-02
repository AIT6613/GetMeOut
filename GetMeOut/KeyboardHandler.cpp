#include "KeyboardHandler.h"



KeyboardHandler::KeyboardHandler()
{
}


KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::update(SDL_Event* event) {
	//check the type of event first
	if (event->type == SDL_KEYDOWN) {
		//keydown is triggered when key is pressed, but not held
		//AND not when the press repeate event fires
		/*
		if (event->key.keysym.scancode == SDL_SCANCODE_R && event->key.repeat == 0) {
			//when user presses R key on keyboard, reset player position
			hero->position.x = 200;
			hero->position.y = 200;
		}
		*/

		// If user press down on title screen
		if (event->key.keysym.scancode == SDL_SCANCODE_DOWN && event->key.repeat == 0) {
			 //check menuPointer, if equal 3, set menuPointer to 1. If not, increase 1
			if (menuPointer != 3)
			{
				menuPointer++;
				hero->position.y += 50;
			}
			else
			{
				//if it is the last menu, go back to first menu
				menuPointer = 1;
				hero->position.y = 340;
			}

		}

		// if player press up in title screen
		if (event->key.keysym.scancode == SDL_SCANCODE_UP && event->key.repeat == 0) {
			//check menuPointer, if equal 3, set menuPointer to 1. If not, increase 1
			if (menuPointer != 1)
			{
				menuPointer--;
				hero->position.y -= 50;
			}
			else
			{
				//if it is the first menu, go back to last menu
				menuPointer = 3;
				hero->position.y = 440;
			}

		}


		// Activities when player press enter in titile screen
		if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && event->key.repeat == 0) {
			menuSelected = true;
		}
	}
}


void KeyboardHandler::updateHeldKeys() {
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

		//set hero action to running
		hero->isHeroRunFlag = true;
		//move hero up
		hero->velocity.y = -500;
		
	} 
	else if (keystates[SDL_SCANCODE_DOWN])
	{
		//set hero action to running
		hero->isHeroRunFlag = true;
		//move hero down
		hero->velocity.y = 500;
		
	} 
	else if (keystates[SDL_SCANCODE_LEFT])
	{
		//set hero action to running
		hero->isHeroRunFlag = true;
		//move hero to the left
		hero->velocity.x = -500;
	} 
	else if (keystates[SDL_SCANCODE_RIGHT])
	{
		//set hero action to running
		hero->isHeroRunFlag = true;
		//move hero to the right
		hero->velocity.x = 500;
	}
	else
	{
		//set hero action to idle
		hero->isHeroRunFlag = false;
	}

		

}

