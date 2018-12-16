#pragma once
#include <SDL.h>
#include "Hero.h"
#include <iostream>

using namespace std;

class InputHandler
{


public:
	Hero* hero;

	InputHandler();
	~InputHandler();


	//abstaract function
	virtual void update(SDL_Event* event) = 0;
};

