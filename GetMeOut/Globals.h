#pragma once
#include <SDL.h>
#include "GameStateMachine.h"
#include "Map.h"

class Globals
{
public:
	Globals();
	~Globals();

	static SDL_Renderer* renderer;
	static bool quitGame;
	static GameStateMachine gameStateMachine;
	static Map* mazeMap;
	static int screenWidth, screenHeight;
	static SDL_Rect camera;

	static int countZombie;

};