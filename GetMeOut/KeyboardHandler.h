#pragma once
#include "InputHandler.h"

class KeyboardHandler :
	public InputHandler
{

//private:
public:
	int menuPointer = 1;
	bool menuSelected = false;

//public:
	KeyboardHandler();
	~KeyboardHandler();

	virtual void update(SDL_Event* event);
	//void updateHeldKeys();
};

