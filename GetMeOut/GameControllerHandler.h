#pragma once
#include "InputHandler.h"
class GameControllerHandler :
	public InputHandler
{
public:
	SDL_GameController* controller = NULL;

	GameControllerHandler();
	~GameControllerHandler();

	void update(SDL_Event* event);
};

