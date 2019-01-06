#include "Globals.h"


Globals::Globals()
{
}


Globals::~Globals()
{
}


SDL_Renderer* Globals::renderer = NULL;
bool Globals::quitGame = false;

GameStateMachine Globals::gameStateMachine;

int Globals::screenWidth = 800;
int Globals::screenHeight = 640;
SDL_Rect Globals::camera;