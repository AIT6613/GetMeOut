#pragma once
#include "InputHandler.h"

class KeyboardHandler :
	public InputHandler
{

//private:
public:
	int menuPointer = 1;	//current selected menu number
	bool menuSelected = false;	//indicate play select menu or not. True is selecting.

//public:
	KeyboardHandler();
	~KeyboardHandler();

	virtual void update(SDL_Event* event);
	//void updateHeldKeys();
};

