#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include "Backgrond.h"
#include "Text.h"
#include "Map.h"
#include "Wall.h"
#include "Dirt.h"

#include "KeyboardHandler.h"

#include <list>

#define BLOCK_WIDTH 120	//width of one block in map
#define BLOCK_HEIGHT 120 //height of one block in map

using namespace std;

int main(int argc, char** argv) {

Private: 
	SDL_Rect sourceRect, destinationRect;

	bool isExitFlag = false;	//check player select menu exit

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
		800, 640, SDL_WINDOW_SHOWN);// |SDL_WINDOW_FULLSCREEN
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



	//loop unit play select exit menu, then close the game
	while (!isExitFlag)
	{

		//list of all our game entities
		list<Entity*> entities;

		//build title background
		Backgrond* titleBackground = new Backgrond();
		titleBackground->setXY(0, 0);	//set position to object
		titleBackground->setWH(800, 600);	//set object size
		titleBackground->setTexture("assets/TitleBackground.png", renderer); //loade texture to object
		//add to list
		entities.push_back(titleBackground);


		//build game title
		Text* gameTitle = new Text();
		gameTitle->setXY(70, 50);//set position to object
		gameTitle->setWH(660, 150);//set object size
		gameTitle->setTexture("assets/GameTitle.png", renderer);//loade texture to object
		//add to list
		entities.push_back(gameTitle);

		//build menu play game
		Text* menuPlayGame = new Text();
		menuPlayGame->setXY(292, 350);//set position to object
		menuPlayGame->setWH(219, 49);//set object size
		menuPlayGame->setTexture("assets/MenuPlayGame.png", renderer);//loade texture to object
		//add to list
		entities.push_back(menuPlayGame);

		//build menu top rank
		Text* menuTopRank = new Text();
		menuTopRank->setXY(292, 400);//set position to object
		menuTopRank->setWH(185, 47);//set object size
		menuTopRank->setTexture("assets/MenuTopRank.png", renderer);//loade texture to object
		//add to list
		entities.push_back(menuTopRank);

		//build menu Exit
		Text* menuExit = new Text();
		menuExit->setXY(292, 450);//set position to object
		menuExit->setWH(76, 32);//set object size
		menuExit->setTexture("assets/MenuExit.png", renderer);//loade texture to object
		//add to list
		entities.push_back(menuExit);



		//HERO
		//create animation for hero
		Animation heroRun("assets/HeroRun.png", renderer, 10, 400, 460, 0.08, 1, 10, 140, 200);
		//build hero
		Hero* hero = new Hero();
		hero->setAnimation(&heroRun);
		hero->setXY(240, 340);
		hero->isHeroRunFlag = true;
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
			//update lastUpdate, so DT is calculated correctly next loop
			lastUpdate = SDL_GetTicks();

			cout << "dt = " << dt << endl;


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
					if (keyboardHandler.menuPointer == 1) {
						loop = false;
					}
					else if (keyboardHandler.menuPointer == 3)
					{
						loop = false;
						//exit loop then close the program
						isExitFlag = true;
					}
						
						

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

		//if select menu is 1, run game play screen
		//list of all our game entities
		loop = true;
		if (keyboardHandler.menuPointer == 1) 
		{
			//CLEAN UP
			SDL_DestroyRenderer(renderer);

			//create renderer (helps you draw stuff to the screen)
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				cout << "Renderer failed!" << endl;
				system("pause");
				return 23;
			}

			//create map
			Map* map = new Map();
			map->loadMapFromFile("assets/Map1.txt");

			//create wall object
			//wallRegular use for regular wall
			Wall* wallRegular = new Wall();
			wallRegular->setWH(BLOCK_WIDTH, BLOCK_HEIGHT);
			wallRegular->setSourceRect(0,0,500,500);
			wallRegular->setTexture("assets/Wall.png", renderer);
			//wall3D use for 2d Wall, make it fill like an 3D
			Wall* wall3D = new Wall();
			wall3D->setWH(BLOCK_WIDTH, BLOCK_HEIGHT);
			wall3D->setSourceRect(500, 0, 500, 500);
			wall3D->setTexture("assets/Wall.png", renderer);
			//dirt use for build map
			Dirt* dirt = new Dirt();
			dirt->setWH(BLOCK_WIDTH, BLOCK_HEIGHT);
			dirt->setSourceRect(0, 0, 500, 500);
			dirt->setTexture("assets/Dirt.png", renderer);
			


			//list of all our game entities
			list<Entity*> entities;

			//HERO
		//create animation for hero
			Animation heroRun("assets/HeroRun.png", renderer, 10, 400, 460, 0.08, 1, 10, 140, 200);
			//build hero
			Hero* hero = new Hero();
			hero->setAnimation(&heroRun);
			hero->setTexture("assets/HeroIdle.png", renderer,1,10,140,200);
			hero->setWH(60, 60);
			hero->setXY(240, 340);
			//add to list
			entities.push_back(hero);








			//setup input handlers
			KeyboardHandler keyboardHandler;
			keyboardHandler.hero = hero;
			
			//to help with working out deltaTime
			Uint32 lastUpdate = SDL_GetTicks();
			while (loop = true) 
			{
				//TIME MANAGEMENT, work out Delta Time (time since last rendering)
				Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
				//convert this to milliseconds over 1 whole second(dt is a fraction)
				float dt = timeDiff / 1000.0;	//e.g 200 is now 0.2
				//update lastUpdate, so DT is calculated correctly next loop
				lastUpdate = SDL_GetTicks();

				cout << "dt = " << dt << endl;

				dt = timeDiff / 1000.0;

				//Check for user inputs

				//loop through all generated input events 

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
					//keyboardHandler.update(&event);
				}

				//check hero movement here
				//hero->moveToRow = (((int)hero->position.y - 500) % BLOCK_HEIGHT) + 1;
				//hero->moveToColumn = (((int)hero->position.x - 500) % BLOCK_HEIGHT) + 1;

				//check held keys OUTSIDE of input polling look
					keyboardHandler.updateHeldKeys();


				for (int i = 0; i < map->row; i++) 
				{
					for (int j = 0; j < map->column; j++) 
					{
						try
						{


							if (map->map[i][j] == 0)
							{
								dirt->setXY(j * BLOCK_WIDTH, i * BLOCK_HEIGHT);
								dirt->draw();
							}
							else if (map->map[i][j] == 1)
							{

								//check if the block lower this block not a dead zone. draw 3d wall for this block.
								if ((i + 1) < map->row)
								{
									if (map->map[i + 1][j] == 1)
									{
										wallRegular->setXY(j * BLOCK_WIDTH, i * BLOCK_HEIGHT);
										wallRegular->draw();
									}
									else
									{
										wall3D->setXY(j * BLOCK_WIDTH, i * BLOCK_HEIGHT);
										wall3D->draw();
									}
								}
								else {
									wallRegular->setXY(j * BLOCK_WIDTH, i * BLOCK_HEIGHT);
									wallRegular->draw();
								}


							}
						} 
						catch (exception ex)
						{
							
						}

					}
				}

				//Loop through entities
				for (Entity* e : entities) {
					e->update(dt);
					e->draw();
				}


				//show the newly drawn up frame of the game
				SDL_RenderPresent(renderer);
			}
		}
		

	}

	//CLEAN UP
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//shuts down all sdl sub systems
	SDL_Quit();


	//system("pause");	

	return 0;
}