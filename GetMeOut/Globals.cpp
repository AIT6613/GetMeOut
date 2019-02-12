#include "Globals.h"


Globals::Globals()
{
	
}


Globals::~Globals()
{
}

//MUST initialise static values outside of class definition
SDL_Renderer* Globals::renderer = NULL;
bool Globals::quitGame = false;

GameStateMachine Globals::gameStateMachine;

Map* Globals::mazeMap;

int Globals::screenWidth = 800;
int Globals::screenHeight = 640;
SDL_Rect Globals::camera;
