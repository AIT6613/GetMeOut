#pragma once
#include "InputHandler.h"
class MouseHandler :
	public InputHandler
{
public:
	bool leftMousePressedDown = false;

	MouseHandler();
	~MouseHandler();

	//override
	void update(SDL_Event* event);
};

