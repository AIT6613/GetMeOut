#pragma once
#include "InputHandler.h"
#include "Map.h"

class KeyboardHandler :
	public InputHandler
{

private:


public:
	KeyboardHandler();
	~KeyboardHandler();


	virtual void update(SDL_Event* event);
	void updateHeldKeys(Map* map);
};

