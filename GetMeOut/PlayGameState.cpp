#include "PlayGameState.h"


PlayGameState::PlayGameState()
{
	//create map
	map = new Map(120, 120);
	map->loadMapFromFile("assets/Map1.txt");

	//create wall object
	//wallRegular use for regular wall
	wallRegular = new Wall();
	wallRegular->setWH(map->blockWidth, map->blockHeight);
	wallRegular->setSourceRect(0, 0, 500, 500);
	wallRegular->setTexture("assets/Wall.png", Globals::renderer);
	//wall3D use for 2d Wall, make it fill like an 3D
	wall3D = new Wall();
	wall3D->setWH(map->blockWidth, map->blockHeight);
	wall3D->setSourceRect(500, 0, 500, 500);
	wall3D->setTexture("assets/Wall.png", Globals::renderer);
	//dirt use for build map
	dirt = new Dirt();
	dirt->setWH(map->blockWidth, map->blockHeight);
	dirt->setSourceRect(0, 0, 500, 500);
	dirt->setTexture("assets/Dirt.png", Globals::renderer);

	//HERO
//create animation for hero
	heroRun = new Animation("assets/HeroRun.png", Globals::renderer, 10, 400, 460, 0.08, 1, 10, 140, 200);
	//build hero
	hero = new Hero();
	hero->setAnimation(heroRun);
	hero->setTexture("assets/HeroIdle.png", Globals::renderer, 1, 10, 140, 200);
	hero->setWH(60, 60);
	hero->setXY(240, 340);
	//add to list
	entities.push_back(hero);


	//setup input handlers
	keyboardHandler.hero = hero;
	mouseHandler.hero = hero;
	controllerHandler.hero = hero;

	//make camera follow hero
	cameraManager.target = hero;


	//to help with working out deltaTime
	lastUpdate = SDL_GetTicks();

}


PlayGameState::~PlayGameState()
{
	//cleanup dynamic 
	delete heroRun;
	delete hero;
	delete wallRegular;
	delete wall3D;
	delete dirt;
	delete map;

}


void PlayGameState::update() {
	//TIME MANAGEMENT, work out Delta Time (time since last rendering)
	Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
	//convert this to milliseconds over 1 whole second(dt is a fraction)
	float dt = timeDiff / 1000.0;	//e.g 200 is now 0.2
	//update lastUpdate, so DT is calculated correctly next loop
	lastUpdate = SDL_GetTicks();

	cout << "dt = " << dt << endl;

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
				//exit loop
				//Globals::quitGame = true;
				Globals::gameStateMachine.pushState(new MenuGameState());
				//return;
			}
		}

		//pass this event into our hero input handlers
		if (controllerHandler.controller != NULL)
			controllerHandler.update(&event);
		else
			keyboardHandler.update(&event);


		mouseHandler.update(&event);
	}
	//check held keys OUTSIDE of input polling look
	keyboardHandler.updateHeldKeys(map);

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

	//draw map by loop array map
	for (int i = 0; i < map->row; i++)
	{
		for (int j = 0; j < map->column; j++)
		{
			try
			{
				//check if array not dead zone
				if (map->map[i][j] == 0)
				{
					//draw dirt. play can walk around
					dirt->setXY(j * map->blockWidth, i * map->blockHeight);
					dirt->draw();
				}
				//check if array is dead zone
				if (map->map[i][j] == 1)
				{
					//check array is not last row
					if ((i + 1) < map->row)
					{
						//check if the block lower this block not a dead zone. 
						if (map->map[i + 1][j] == 1)
						{
							//draw 3d wall for this block.
							wallRegular->setXY(j * map->blockWidth, i * map->blockHeight);
							wallRegular->draw();
						}
						else
						{
							//draw regular wall
							wall3D->setXY(j * map->blockWidth, i * map->blockHeight);
							wall3D->draw();
						}
					}
					else {
						//draw regular wall
						wallRegular->setXY(j * map->blockWidth, i * map->blockHeight);
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

