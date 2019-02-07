#include "PlayGameState.h"


PlayGameState::PlayGameState()
{
	// TODO: get gameplay criteria from file
	// read level from file
	// read gameplay criteria from file by use level to select which one need
	// zombie appear time, curl item appear time, damage HP per time, incrase HP per curl item.


	//create map
	map = new Map();
	map->setArrayBlockSize(240, 240);
	map->loadMapFromFile("assets/Map1.txt");


	//link map to mazeMap that is global. can use any where because have a lot of function relate wiht map
	Globals::mazeMap = map;

	//dirt use for build map
	dirt = new Dirt();
	dirt->setWH(map->blockWidth, map->blockHeight);
	dirt->setSourceRect(0, 0, 500, 500);
	dirt->setTexture("assets/Dirt.png", Globals::renderer);
	entities.push_back(dirt);


	//wallRegular use for regular wall
	wall = new Wall();
	wall->setWH(map->blockWidth, map->blockHeight);
	entities.push_back(wall);

	
	//HERO
//create animation for hero
	//heroRun = new Animation("assets/HeroRun.png", Globals::renderer, 10, 400, 460, 0.08, 1, 10, 140, 200);
	//Loading up a png into a texture
	SDL_Surface* heroRunSurface = IMG_Load("assets/HeroRun.png");

	SDL_SetColorKey(heroRunSurface, 1, SDL_MapRGB(heroRunSurface->format, 10, 140, 200));

	//convert surface to texture
	SDL_Texture* heroRunSpriteSheet = SDL_CreateTextureFromSurface(Globals::renderer, heroRunSurface); //=IMG_LoadTexture
	//heroRunAnimation = new Animation(heroRunSpriteSheet, Globals::renderer, 10, 400, 460, 0.08);	//0.2 = 200ms per frame duration

	//build hero
	hero = new Hero();
	
	hero->setAnimation(heroRunSpriteSheet, Globals::renderer, 10, 400, 460, 0.08);
	hero->setTexture("assets/HeroIdle.png", Globals::renderer, 1, 10, 140, 200);
	hero->setWH(90, 90);
	hero->setXY(500, 500);
	//add to list
	entities.push_back(hero);
	


	//add zombie to the game

	//create animation for zomebie
	//zombieAnimation = new Animation("assets/Zombie.png", Globals::renderer, 10, 310, 400, 0.16, 1, 210, 10, 190);

	//Loading up a png into a texture
	SDL_Surface* zombieSurface = IMG_Load("assets/Zombie.png");

	SDL_SetColorKey(zombieSurface, 1, SDL_MapRGB(zombieSurface->format, 210, 10, 190));

	//convert surface to texture
	SDL_Texture* zombieSpriteSheet = SDL_CreateTextureFromSurface(Globals::renderer, zombieSurface); //=IMG_LoadTexture
	//zombieAnimation = new Animation(runSpriteSheet, Globals::renderer, 10, 310, 400, 0.16);	//0.2 = 200ms per frame duration


	//build zombie
	zombie = new Zombie();
	zombie->setAnimation(zombieSpriteSheet, Globals::renderer, 10, 310, 400, 0.16);
	zombie->setWH(90, 90);
	zombie->setXY(600, 600);
	//add to list
	entities.push_back(zombie);



	//setup input handlers
	keyboardHandler.hero = hero;
	mouseHandler.hero = hero;
	controllerHandler.hero = hero;

	//make camera follow hero
	cameraManager.target = hero;

	/*
	// TODO: load front here
	//LOAD UP OUR AWESOME FONT
	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);	//font location, font size
	SDL_Color textColor = { 125,0,34,0 };//r, g, b a   0-255 each

	//Gerate surface from font + string
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "It's nearly Xmas!", textColor);
	//convert to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);

	//text destination
	SDL_Rect textDestination;
	textDestination.x = 100;
	textDestination.y = 250;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);
	*/


	//to help with working out deltaTime
	lastUpdate = SDL_GetTicks();

}


PlayGameState::~PlayGameState()
{
	//cleanup dynamic 
	delete heroRunAnimation;
	delete hero;
	delete wall;
	delete dirt;
	delete map;
	delete zombieAnimation;
	delete zombie;

	//Loop through entities
	for (Entity* e : entities) {
		//delete and disalocate memory
		delete e;
	}

}


void PlayGameState::update() {

	/*
	//LOAD UP OUR AWESOME FONT
	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);	//font location, font size
	SDL_Color textColor = { 125,0,34,0 };//r, g, b a   0-255 each

	//Gerate surface from font + string
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "It's nearly Xmas!", textColor);
	//convert to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);

	//text destination
	SDL_Rect textDestination;
	textDestination.x = 100;
	textDestination.y = 250;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);
	*/

	//TIME MANAGEMENT, work out Delta Time (time since last rendering)
	Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
	//convert this to milliseconds over 1 whole second(dt is a fraction)
	float dt = timeDiff / 1000.0;	//e.g 200 is now 0.2
	//update lastUpdate, so DT is calculated correctly next loop
	lastUpdate = SDL_GetTicks();

	//cout << "dt = " << dt << endl;

	dt = timeDiff / 1000.0;

	//Check for user inputs
	SDL_Event event;
	//loop through all generated input events 
	while (SDL_PollEvent(&event)) {
		//check if the user closed the window/screen
		if (event.type == SDL_QUIT) {
			//exit loop
			Globals::quitGame = true;
			return;
		}
		//check for keyboard events
		if (event.type == SDL_KEYDOWN) {
			//if ESC pressed, exit game
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				
				
				

				Globals::gameStateMachine.popState();
			

				return;
			}
		}

		//pass this event into our hero input handlers
		if (controllerHandler.controller != NULL)
			controllerHandler.update(&event);
		else
			keyboardHandler.update(&event);


		mouseHandler.update(&event);
	}
	
	keyboardHandler.updateHeldKeys(map);


	//drop zombie in to play screen by random an allow space from map array
	//check the time count before drop zombie
	if (countTimeZombie >= 1)  // TODO: this number of time count should read from level file
	{
		// TODO: random allow space, drop zombie over there
		//random for row and column
		
		//check map block is not dead zone or not
		isPutZombie = false;

		while (!isPutZombie)
		{
			randX = rand() % Globals::mazeMap->row;
			randY = rand() % Globals::mazeMap->column;

			if (Globals::mazeMap->map[randX][randY] == 0)
			{
				//Loading up a png into a texture
				SDL_Surface* zombieSurface = IMG_Load("assets/Zombie.png");

				SDL_SetColorKey(zombieSurface, 1, SDL_MapRGB(zombieSurface->format, 210, 10, 190));

				//convert surface to texture
				SDL_Texture* zombieSpriteSheet = SDL_CreateTextureFromSurface(Globals::renderer, zombieSurface);

				zombie = new Zombie();
				zombie->setAnimation(zombieSpriteSheet, Globals::renderer, 10, 310, 400, 0.16);

				// TODO: change zombie location here

				zombie->setWH(90, 90);
				zombie->setXY(600, 600);


				entities.push_back(zombie);

				Globals::countZombie++;

				cout << "Zombie count : " + Globals::countZombie << endl;
				isPutZombie = true;
			}
		}
		

		//zombie->addZomebieToScreen();

		countTimeZombie = 0;
	}
	else
		countTimeZombie += dt;

	
	// TODO: Drop curl item to the map


	//Loop through entities
	for (Entity* e : entities) {
		e->update(dt);
	}

	//update cameras position after hero moving in the world
	cameraManager.update();
}


void PlayGameState::render() {


	//Clear render
	SDL_RenderClear(Globals::renderer);

	//Loop through entities
	for (Entity* e : entities) {
		e->draw();
	}

	//show the newly drawn up frame of the game
	SDL_RenderPresent(Globals::renderer);

}
bool PlayGameState::onEnter() {
	cout << "enter play game state" << endl;
	return true;

}
bool PlayGameState::onExit() {
	cout << "exit play game state" << endl;
	return true;
}
