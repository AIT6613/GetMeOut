#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include "Backgrond.h"
#include "Text.h"
#include "Map.h"
#include "Wall.h"
#include "Dirt.h"
#include "Globals.h"
#include "CameraManager.h"
#include "KeyboardHandler.h"
#include "GameControllerHandler.h"
#include "MouseHandler.h"
#include <list>
#include "MenuGameState.h"
#include <stdlib.h> // rand()
#include <time.h> //access to time function

using namespace std;

int main(int argc, char** argv) {

	//set random series seed value
	srand(time(NULL));	//you can get same number series by re-using a seed value e.g srand(5);

	//initialise sdl2 subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL failed to initialise!!!" << endl;
		system("pause");
		return -1;
	}
	else
		cout << "Success!" << endl;

	//initialise SDL image
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & IMG_INIT_PNG | IMG_INIT_JPG)) {
		cout << "sdl image did load: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//create a window to draw into
	//params: title of window
	//		  x and y of where to put this window (we are just centering it)
	//	      width and height of window in pixels
	//		  flags to help decide what type of window to use
	SDL_Window* window = SDL_CreateWindow("Get Me Out!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN);// |SDL_WINDOW_FULLSCREEN

	//setup camera size and position for first time use
	Globals::camera.x = 0;
	Globals::camera.y = 0;
	Globals::camera.w = Globals::screenWidth;
	Globals::camera.h = Globals::screenHeight;

	//check window working or not
	if (window == NULL) {
		cout << "Couldn't make window!!!" << endl;
		system("pause");
		return 78789;
	}


	//Init TTF
	if (TTF_Init() != 0) {
		//if failed
		cout << "SDL TTF FAILED!" << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	//create renderer (helps you draw stuff to the screen)
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "Renderer failed!" << endl;
		system("pause");
		return 23;
	}

	//make global renderer pointer point to the renderer we just built
	Globals::renderer = renderer;

	//start on menu screen
	Globals::gameStateMachine.pushState(new MenuGameState());

	bool loop = true;
	while (loop)
	{
		Globals::gameStateMachine.update();
		Globals::gameStateMachine.render();

		if (Globals::quitGame || Globals::gameStateMachine.gameStates.empty())
			loop = false;
	}

	//clean up any extra screen states
	Globals::gameStateMachine.clearAll();

	//CLEAN UP
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//shuts down all sdl sub systems
	SDL_Quit();


	//system("pause");	
	return 0;
}