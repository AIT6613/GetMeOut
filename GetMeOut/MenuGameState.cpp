#include "MenuGameState.h"


MenuGameState::MenuGameState()
{
	//build title background
	titleBackground = new Backgrond();
	titleBackground->setXY(0, 0);	//set position to object
	titleBackground->setWH(800, 640);	//set object size
	titleBackground->setTexture("assets/TitleBackground.png", Globals::renderer); //loade texture to object
	//add to list
	entities.push_back(titleBackground);

	//build game title
	gameTitle = new Text();
	gameTitle->setXY(70, 50);//set position to object
	gameTitle->setWH(660, 150);//set object size
	gameTitle->setTexture("assets/GameTitle.png", Globals::renderer);//loade texture to object
	//add to list
	entities.push_back(gameTitle);

	//build menu play game
	menuPlayGame = new Text();
	menuPlayGame->setXY(292, 350);//set position to object
	menuPlayGame->setWH(219, 49);//set object size
	menuPlayGame->setTexture("assets/MenuPlayGame.png", Globals::renderer);//loade texture to object
	//add to list
	entities.push_back(menuPlayGame);

	//build menu top rank
	menuTopRank = new Text();
	menuTopRank->setXY(292, 400);//set position to object
	menuTopRank->setWH(185, 47);//set object size
	menuTopRank->setTexture("assets/MenuTopRank.png", Globals::renderer);//loade texture to object
	//add to list
	entities.push_back(menuTopRank);

	//build menu Exit
	menuExit = new Text();
	menuExit->setXY(292, 450);//set position to object
	menuExit->setWH(76, 32);//set object size
	menuExit->setTexture("assets/MenuExit.png", Globals::renderer);//loade texture to object
	//add to list
	entities.push_back(menuExit);

	//HERO
	//create animation for hero
	heroRun = new Animation("assets/HeroRun.png", Globals::renderer, 10, 400, 460, 0.08, 1, 10, 140, 200);
	//build hero
	hero = new Hero();
	hero->setAnimation(heroRun);
	hero->setXY(240, 340);
	hero->isHeroRunFlag = true;
	//add to list
	entities.push_back(hero);


	//setup input handlers
	KeyboardHandler keyboardHandler;
	keyboardHandler.hero = hero;
}


MenuGameState::~MenuGameState()
{
	//cleanup dynamic memory
	delete heroRun;
	delete hero;
	delete titleBackground;
	delete gameTitle;
	delete menuPlayGame;
	delete menuTopRank;
	delete menuExit;
}


void MenuGameState::update() {

	//TIME MANAGEMENT, work out Delta Time (time since last rendering)
	Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
	//convert this to milliseconds over 1 whole second(dt is a fraction)
	dt = timeDiff / 1000.0;	//e.g 200 is now 0.2
   //update lastUpdate, so DT is calculated correctly next loop
	lastUpdate = SDL_GetTicks();

	cout << "dt = " << dt << endl;


	//Check for user inputs
	SDL_Event event;
	//loop through all generated input events 
	while (SDL_PollEvent(&event)) {
		//exit when pressing window close button
		if (event.type == SDL_QUIT) {
			Globals::quitGame = true;
			Globals::gameStateMachine.popState();
			return;
		}
		//user press button on keyboard
		if (event.type == SDL_KEYDOWN) {
			//check press button is escape
			//if yes, exit game
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				Globals::quitGame = true;
				Globals::gameStateMachine.popState();
				return;
			}
			//check press button is space
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				//start game
				Globals::gameStateMachine.pushState(new PlayGameState());
			}
			// If user press down on title screen
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				//check menuPointer, if equal 3, set menuPointer to 1. If not, increase 1
				if (menuPointer != 3)
				{
					menuPointer++;
					hero->position.y += 50;
				}
				else
				{
					//if it is the last menu, go back to first menu
					menuPointer = 1;
					hero->position.y = 340;
				}

			}
			// if player press up in title screen
			if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
				//check menuPointer, if equal 3, set menuPointer to 1. If not, increase 1
				if (menuPointer != 1)
				{
					menuPointer--;
					hero->position.y -= 50;
				}
				else
				{
					//if it is the first menu, go back to last menu
					menuPointer = 3;
					hero->position.y = 440;
				}

			}
			// Activities when player press enter in titile screen
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				//check if menu point a play game
				if (menuPointer == 1)
					//start game
					Globals::gameStateMachine.pushState(new PlayGameState());
				//check if user select to see top rank screen
				if (menuPointer == 2)
					//show top rank screen
				{

				}
				//check if user select exit menu
				if (menuPointer == 3)
				{
					// exit game
					Globals::quitGame = true;
					Globals::gameStateMachine.popState();
					return;
				}
			}
		}

	}


	//Loop through entities
	for (Entity* e : entities) {
		e->update(dt);
	}

}

void MenuGameState::render() {

	//clear the previous draw
	SDL_RenderClear(Globals::renderer);

	//Loop through entities
	for (Entity* e : entities) {
		e->draw();
	}

	//show the newly drawn up frame of the game
	SDL_RenderPresent(Globals::renderer);

}


bool MenuGameState::onEnter() {
	cout << "Entering menu state" << endl;
	return true;
}
bool MenuGameState::onExit() {
	cout << "Exiting menu state" << endl;
	return true;
}