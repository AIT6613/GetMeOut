#pragma once
#include "InputHandler.h"

class KeyboardHandler :
	public InputHandler
{

private:
	int menuPointer = 1;

public:
	KeyboardHandler();
	~KeyboardHandler();

	virtual void update(SDL_Event* event);
	//void updateHeldKeys();
};

