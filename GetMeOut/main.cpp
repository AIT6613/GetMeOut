#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include "TitleBackgrond.h"
#include "Text.h"

#include "KeyboardHandler.h"

#include <list>

using namespace std;

int main(int argc, char** argv) {
Private: 
	SDL_Rect sourceRect, destinationRect;

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

	
	

	//list of all our game entities
	list<Entity*> entities;

	
	//LOAD UP Title Background
	//load image up as surface
	SDL_Surface* titleBackgroundSurface = IMG_Load("assets/TitleBackground.png");
	//next, convert to texture 
	SDL_Texture* titleBackgroundTexture = SDL_CreateTextureFromSurface(renderer, titleBackgroundSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(titleBackgroundSurface);

	//setting up source rectangle for knight texture
	sourceRect = { 0,0,800,600 }; //x=0, y=0 w=0 h=0

	destinationRect = { 0,0,800,600 };

	//build title background
	TitleBackgrond* titleBackground = new TitleBackgrond();
	titleBackground->setXY(100, 100);
	titleBackground->setWH(300, 300);
	titleBackground->setTexture(titleBackgroundTexture, sourceRect, destinationRect);
	titleBackground->setRenderer(renderer);
	//add to list
	entities.push_back(titleBackground);
	
	

	//LOAD UP Game Title
	//load image up as surface
	SDL_Surface* gameTitleSurface = IMG_Load("assets/GameTitle.png");
	//next, convert to texture 
	SDL_Texture* gameTitleTexture = SDL_CreateTextureFromSurface(renderer, gameTitleSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(gameTitleSurface);

	//setting up source rectangle for knight texture
	sourceRect = { 0,0,660,150 }; //x=0, y=0 w=0 h=0

	destinationRect = { 70,50,660,150 };

	//build title background
	Text* gameTitle = new Text();
	gameTitle->setXY(100, 100);
	gameTitle->setWH(660, 150);
	gameTitle->setTexture(gameTitleTexture, sourceRect, destinationRect);
	gameTitle->setRenderer(renderer);
	//add to list
	entities.push_back(gameTitle);



	//LOAD UP menu play game
	//load image up as surface
	SDL_Surface* menuPlayGameSurface = IMG_Load("assets/MenuPlayGame.png");
	//next, convert to texture 
	SDL_Texture* menuPlayGameTexture = SDL_CreateTextureFromSurface(renderer, menuPlayGameSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(menuPlayGameSurface);

	//setting up source rectangle for knight texture
	sourceRect = { 0,0,219,49 }; //x=0, y=0 w=0 h=0

	destinationRect = { 292,350,219,49 };

	//build menu play game
	Text* menuPlayGame = new Text();
	menuPlayGame->setXY(100, 100);
	menuPlayGame->setWH(219, 49);
	menuPlayGame->setTexture(menuPlayGameTexture, sourceRect, destinationRect);
	menuPlayGame->setRenderer(renderer);
	//add to list
	entities.push_back(menuPlayGame);



	//LOAD UP menu top rank
	//load image up as surface
	SDL_Surface* menuTopRankSurface = IMG_Load("assets/MenuTopRank.png");
	//next, convert to texture 
	SDL_Texture* menuTopRankTexture = SDL_CreateTextureFromSurface(renderer, menuTopRankSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(menuTopRankSurface);

	//setting up source rectangle for knight texture
	sourceRect = { 0,0,185,47 }; //x=0, y=0 w=0 h=0

	destinationRect = { 292,400,185,47 };

	//build menu top rank
	Text* menuTopRank = new Text();
	menuTopRank->setXY(100, 100);
	menuTopRank->setWH(185, 47);
	menuTopRank->setTexture(menuTopRankTexture, sourceRect, destinationRect);
	menuTopRank->setRenderer(renderer);
	//add to list
	entities.push_back(menuTopRank);




	//LOAD UP menu Exit
	//load image up as surface
	SDL_Surface* menuExitSurface = IMG_Load("assets/MenuExit.png");
	//next, convert to texture 
	SDL_Texture* menuExitTexture = SDL_CreateTextureFromSurface(renderer, menuExitSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(menuExitSurface);

	//setting up source rectangle for knight texture
	sourceRect = { 0,0,76,32 }; //x=0, y=0 w=0 h=0

	destinationRect = { 292,450,76,32 };

	//build menu Exit
	Text* menuExit = new Text();
	menuExit->setXY(100, 100);
	menuExit->setWH(76, 32);
	menuExit->setTexture(menuExitTexture, sourceRect, destinationRect);
	menuExit->setRenderer(renderer);
	//add to list
	entities.push_back(menuExit);








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

	//free up its memory
	SDL_FreeSurface(heroSurface);

	Animation anim1(heroSpriteSheet, renderer, 10, 400, 460, 0.08);

	//build a hero
	Hero* hero = new Hero();
	hero->setAnimation(&anim1);
	hero->setRenderer(renderer);
	hero->setXY(240, 340);
	//add to list
	entities.push_back(hero);





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




		//draw title background
		//SDL_RenderCopy(renderer, titleBackgroundTexture, &sourceRect, &destinationRect);



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


				if (keyboardHandler.menuSelected) {
					if (keyboardHandler.menuPointer == 3)
						loop = false;
					
					keyboardHandler.menuSelected = false;
				}

		}
		//check held keys OUTSIDE of input polling loop
			//keyboardHandler.updateHeldKeys();




		//Loop through entities
		for (Entity* e : entities) {
			e->update(dt);
			e->draw();
		}


		//show the newly drawn up frame of the game
		SDL_RenderPresent(renderer);

	}

	//CLEAN UP
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//shuts down all sdl sub systems
	SDL_Quit();


	//system("pause");

	return 0;
}