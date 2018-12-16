#pragma once
#include "InputHandler.h"
class KeyboardHandler :
	public InputHandler
{
public:
	KeyboardHandler();
	~KeyboardHandler();

	virtual void update(SDL_Event* event);
	void updateHeldKeys();
};

