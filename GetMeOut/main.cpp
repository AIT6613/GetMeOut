#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include "TitleBackgrond.h"

#include "KeyboardHandler.h"

#include <list>

using namespace std;

int main(int argc, char** argv) {
	//initialise sdl2 subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL failed to initialise!!!" << endl;
		system("pause");
		return -1;
	}
	else
	{
		cout << "Success!" << endl;
	}

	//initialise sdl image
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & IMG_INIT_PNG | IMG_INIT_JPG)) {
		cout << "sdl image did load: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//create a window
	SDL_Window* window = SDL_CreateWindow("Get Me Out!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN);// |SDL_WINDOW_FULLSCREEN
	if (window == NULL) {
		cout << "Couldn't make window!!!" << endl;
		system("pause");
		return 78789;
	}

	//create renderer (helps you draw stuff to the screen)
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "Renderer failed!" << endl;
		system("pause");
		return 23;
	}

	
	SDL_Surface* heroSurface = IMG_Load("assets/HeroRun.png");

	//set background of sprite to be transparent
	//params: surface to change
	//		1 = turn on,  0 = turn off
	//		which colour to user as colour key (SDL_MapRGB will find closest colour match in the surface to set it to)
	SDL_SetColorKey(heroSurface, 1, SDL_MapRGB(heroSurface->format, 10, 140, 200));

	//convert surface to texture
	SDL_Texture* heroSpriteSheet = SDL_CreateTextureFromSurface(renderer, heroSurface); //=IMG_LoadTexture(renderer, "assets/run.png"); load png straigth into texture
	//1 frme is 32x32 pixels in this animation, so our source rectangle will be this big
	//SDL_Rect runSourceRect = { 0,0,32,32 }; // x=0, y=0, w=0, h=0

	//SDL_Rect runDestRect = { 0,0,32,32 };

	Animation anim1(heroSpriteSheet, renderer, 9, 400, 460, 0.06);

	//list of all our game entities
	list<Entity*> entities; 


	/*

	//build title background
	TitleBackgrond* titleBackground = new TitleBackgrond();
	titleBackground->setXY(0, 0);
	titleBackground->setWH(300, 300);
	titleBackground->setRenderer(renderer);
	//add to list
	entities.push_back(titleBackground);
	*/



	//build a hero
	Hero* hero = new Hero();
	hero->setAnimation(&anim1);
	hero->setRenderer(renderer);
	hero->setXY(200, 200);
	//add to list
	entities.push_back(hero);



	
	//LOAD UP STUPID KNIGTH.bmp file
	//load image up as surface
	SDL_Surface* titleBackgroundSurface = IMG_Load("assets/TitleBackground.png");
	//NOTE: if you want to programatically screw with image pixel data, do it in when its in surface form
	//next, convert to texture (textures live in the graphics card, which speeds up rendering)
	SDL_Texture* titleBackgroundTexture = SDL_CreateTextureFromSurface(renderer, titleBackgroundSurface);
	//once we are finished with surface, free up its memory
	//SDL_FreeSurface(titleBackgroundSurface);

	//setting up source rectangle for knight texture
	SDL_Rect sourceRect = { 0,0,800,600 }; //x=0, y=0 w=0 h=0

	SDL_Rect destinationRect = { 0,0,800,600 };
	


	//setup input handlers
	KeyboardHandler keyboardHandler;
	keyboardHandler.hero = hero;
	   

	//to help with working out deltaTime
	Uint32 lastUpdate = SDL_GetTicks();

	//GAME LOOP
	bool loop = true;
	while (loop)
	{
		//TIME MANAGEMENT, work out Delta Time (time since last rendering)
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert this to milliseconds over 1 whole second(dt is a fraction)
		float dt = timeDiff / 1000.0;	//e.g 200 is now 0.2
		//make sure youu always update lastUpdate so DT is calculated correctly next loop
		lastUpdate = SDL_GetTicks();

		cout << "dt = " << dt << endl;

		//set current drawing colour for renderer
		SDL_SetRenderDrawColor(renderer, 255, 0, 168, 255);
		//clear screen using current draw colour
		SDL_RenderClear(renderer);

		//change draw colour for rectangle
		SDL_SetRenderDrawColor(renderer, 0, 228, 255, 255);

		//make a rectangle object( x, y, w, h)
		SDL_Rect rect = { 100,50, 300, 240 };

		//draw a filled in rectangle
		SDL_RenderFillRect(renderer, &rect);

		//draw our knight
		SDL_RenderCopy(renderer, titleBackgroundTexture, &sourceRect, &destinationRect);

		//drow our run animation
		/*
		int const runNumberOfFrames = 4;
		runSourceRect.x = runSourceRect.w * int((SDL_GetTicks() / 100) % runNumberOfFrames);
		SDL_RenderCopy(renderer, runSpriteSheet, &runSourceRect, &runDestRect);
		*/

		//Check for user inputs
		SDL_Event event;
		//loop through all generated input events 
		while (SDL_PollEvent(&event)) {
			//check if the user closed the window/screen
			if (event.type == SDL_QUIT) {
				loop = false;
			}
			//check for keyboard events
			if (event.type == SDL_KEYDOWN) {
				//if ESC pressed, exit game
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					loop = false;
				}
			}
			//pass event object to our handlers

				keyboardHandler.update(&event);

		}
		//check held keys OUTSIDE of input polling loop
			keyboardHandler.updateHeldKeys();



		/*
		//pass event object to our handlers
			//if (gameControllerHandler.controller != NULL)
				//gameControllerHandler.update(&event);
			//else
				keyboardHandler.update(&event);


		}
		//check held keys OUTSIDE of input polling loop
		//if (gameControllerHandler.controller != NULL)
			keyboardHandler.update(&event);

			mouseHandler.update(&event);
			*/
			/*
			//update animations
			anim1.update(dt);
			anim2.update(dt);
			anim3.update(dt);
			//draw animations
			anim1.draw(200, 50);
			anim2.draw(200, 100, 5.0f);
			anim3.draw(200, 150, true);
			*/

			//Loop through entities
			//IF you have > VS2010
		for (Entity* e : entities) {
			e->update(dt);
			e->draw();
		}


		//show the newly drawn up frame of the game
		SDL_RenderPresent(renderer);


		//if the game has run for 5 seconds (5000ms)
		//if (SDL_GetTicks() > 5000)
			//loop = false;	//quit the loop

	}

	//SDL_Delay(5000);//pause game for 5000ms

	//CLEAN UP
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//shuts down all sdl sub systems
	SDL_Quit();


	system("pause");

	return 0;
}