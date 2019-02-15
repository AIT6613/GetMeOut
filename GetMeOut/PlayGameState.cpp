#include "PlayGameState.h"


PlayGameState::PlayGameState()
{
	//create map
	map = new Map();
	map->setArrayBlockSize(240, 240);
	map->loadMapFromFile("assets/Map1.txt");

	//load game condition
	//Read level condition from file
	//in this case read level 1.
	// TODO: get level from menu then read file depend on selected menu
	string textString;
	string filePath;

	// make sure to clear player name and playing time
	playerName = "";
	playingTime = 0;
	
	//read game play condition from file. 
	if (Globals::gamePlayLevel == 1)
		filePath = "assets/Level1.txt";
	else if(Globals::gamePlayLevel == 2)
		filePath = "assets/Level2.txt";

	ifstream mapFile(filePath);

	//1 line is zombie gen time
	getline(mapFile, textString);
	Globals::zombieGenTime = atoi(textString.c_str());
	//2 line is curl gen time
	getline(mapFile, textString);
	Globals::healItemGenTime= atoi(textString.c_str());
	//3 line is damage per time
	getline(mapFile, textString);
	Globals::damagePoint = atoi(textString.c_str());
	//4 line is heal point per time
	getline(mapFile, textString);
	Globals::healPoint = atoi(textString.c_str());
	//5 line is heal point per time
	getline(mapFile, textString);
	Globals::zomebieSpeed = atoi(textString.c_str());
	//set start hero heal point to full (100)
	Globals::heroHealPoint = 100;



	//link map to mazeMap that is global. can use any where because have a lot of function relate wiht map
	Globals::mazeMap = map;

	Entity::entities = &entities;

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


	//setup input handlers
	keyboardHandler.hero = hero;
	mouseHandler.hero = hero;
	controllerHandler.hero = hero;

	//make camera follow hero
	cameraManager.target = hero;

	// TODO: load front here
	//LOAD UP OUR AWESOME FONT
	TTF_Font* font = TTF_OpenFont("assets/gooddog.otf", 32);	//font location, font size
	SDL_Color textColor = { 250,0,210,0 };//r, g, b a   0-255 each

	//Gerate surface from font + string
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "It's nearly Xmas!", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);

	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = 100 - Globals::camera.x;
	textDestination->y = 250 - Globals::camera.y;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);


	//to help with working out deltaTime
	lastUpdate = SDL_GetTicks();

	//set time start
	startTime = SDL_GetTicks();

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
	delete heal;
	delete textTexture;
	delete textDestination;
	delete zombieSurface;

	//Loop through entities
	for (Entity* e : entities) {
		//delete and disalocate memory
		delete e;
	}


	//CLEAN UP TEXTURES
	SDL_DestroyTexture(textTexture);
	//Cleanup font
	TTF_CloseFont(font);

}

void PlayGameState::updateHighScore(string playerName, int playingTime)
{
	string textString;
	string filePath;
	

	// set file path depend on player game level
	if (Globals::gamePlayLevel == 1)
		filePath = "assets/HighScoreLevel1.txt";
	else if (Globals::gamePlayLevel == 2)
		filePath = "assets/HighScoreLevel2.txt";

	//Read map file
	ifstream readFile(filePath);

	//create new row for array
	string** scoreBoard;
	scoreBoard = new string*[10];
	for (int i = 0; i < 10; ++i)
		//crate new column for array
		scoreBoard[i] = new string[2];
	
	//read score board from file
	int currentPosition = 0;
	for (int i = 0; i < 10; i++) {
		//get string line from file
		//read 2 line for one record,
		//first line is name
		if (getline(readFile, textString))
		{
			currentPosition = i;
			scoreBoard[i][0] = textString.c_str();
		}
		else
		{
			exit;
		}
		//second line is score
		if (getline(readFile, textString))
		{
			scoreBoard[i][1] = textString.c_str();
		}
		
		//compare if new score is in the scoreboard
		
		int p = atoi(scoreBoard[i][1].c_str());
		if (p > playingTime && playingTime != 0)
		{
			//keep current record to temporary variable
			string tmpName, tmpPlayingTime;
			tmpName = scoreBoard[i][0];
			tmpPlayingTime = scoreBoard[i][1];
			//insert new record to scoreboarad array
			scoreBoard[i][0] = playerName;
			scoreBoard[i][1] = to_string(playingTime);
			//insert temporary record to score board array
			i++;
			currentPosition = i;
			scoreBoard[i][0] = tmpName;
			scoreBoard[i][1] = tmpPlayingTime;
			//reset playername and playing time to noting
			playerName = "";
			playingTime = 0;

		}

	}
	readFile.close();


	//if record not full and player score is the last one, add to score board array
	if (playerName != "" && playingTime != 0)
	{
		if (scoreBoard[currentPosition][0] != "")
			currentPosition++;

		scoreBoard[currentPosition][0] = playerName;
		scoreBoard[currentPosition][1] = to_string(playingTime);
		// reset player name and playing time to nothing
		playerName = "";
		playingTime = 0;

	}

	//update high score file
	//clear all data
	//input new data
	/*
	for (int i = 0; i < 10; i++)
	{
		cout << scoreBoard[i][0] << "  " << scoreBoard[i][1] << endl;
	}
	*/
	ofstream writeFile(filePath, std::ios::out | std::ios::trunc);
	
	for (int i = 0; i < 10; i++)
	{
		if (scoreBoard[i][0].c_str() != "")
		{
			writeFile << scoreBoard[i][0] << endl;
			writeFile << scoreBoard[i][1] << endl;
		}
		else
		{
			exit;
		}
		
	}
	writeFile.close();

}


void PlayGameState::update() {

	//clear out old text texture
	if (textTexture != NULL)
		SDL_DestroyTexture(textTexture);

	//LOAD UP OUR AWESOME FONT
	TTF_Font* font = TTF_OpenFont("assets/gooddog.otf", 32);	//font location, font size
	SDL_Color textColor = { 250,0,210,0 };//r, g, b a   0-255 each
	//set text to show during the game play
	double s(fabs((SDL_GetTicks()-startTime) / 1000));
	int time_target =(SDL_GetTicks()-startTime) / 1000;
	int hour = time_target / 3600;
	int second = time_target % 3600;
	int minute = second / 60;
	second = (time_target - (hour * 3600)) % 60;

	std::stringstream ss;
	ss << "HP: " << Globals::heroHealPoint << "/100 ";
	ss << "      Time Playing: " << hour << ":" << minute << ":" << second;
	ss << "      Zombies: " << countZombie;
	//ss << "    Heal item: " << countHealItem;
	//Gerate surface from font + string
	SDL_Surface * textSurface = TTF_RenderText_Blended(font, ss.str().c_str(), textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);

	//text destination
	textDestination;
	textDestination->x = (hero->position.x -380) - Globals::camera.x;
	textDestination->y = (hero->position.y-300) - Globals::camera.y;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	
	

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
	if (countTimeZombie >= Globals::zombieGenTime)  // TODO: this number of time count should read from level file
	{
		// TODO: random allow space, drop zombie over there
		//Loading up a png into a texture
		zombieSurface = IMG_Load("assets/Zombie.png");

		SDL_SetColorKey(zombieSurface, 1, SDL_MapRGB(zombieSurface->format, 210, 10, 190));

		//convert surface to texture
		SDL_Texture* zombieSpriteSheet = SDL_CreateTextureFromSurface(Globals::renderer, zombieSurface);

		zombie = new Zombie();
		zombie->setAnimation(zombieSpriteSheet, Globals::renderer, 10, 310, 400, 0.16);

		zombie->setWH(90, 90);

		//random free space to put zombie
		int r = rand() % Globals::mazeMap->freeSpaceRows;
		zombie->setXY(Globals::mazeMap->freeSpace[r][1] * Globals::mazeMap->blockWidth, Globals::mazeMap->freeSpace[r][0] * Globals::mazeMap->blockHeight);

		entities.push_back(zombie);

		countZombie++;
		cout << "Zombie count : " << countZombie << "Heal item : " << countHealItem << endl;
			

		countTimeZombie = 0;
	}
	else
		countTimeZombie += dt;

	/*
	// Drop heal item to the map
	//check the time count before drop heal item
	if (countTimeHealItem >= Globals::healItemGenTime)  // TODO: this number of time count should read from level file
	{

		//create header and cpp for CurlItem
		heal = new Heal();
		heal->setWH(30, 30);
		heal->setSourceRect(0, 0, 400, 400);
		heal->setTexture("assets/HealItem.png", Globals::renderer);

		//random free space to put heal item
		int r = rand() % Globals::mazeMap->freeSpaceRows;
		heal->setXY((Globals::mazeMap->freeSpace[r][1] * Globals::mazeMap->blockWidth) + (Globals::mazeMap->blockWidth/2), (Globals::mazeMap->freeSpace[r][0] * Globals::mazeMap->blockHeight) + (Globals::mazeMap->blockHeight / 2));

		entities.push_back(heal);

		countHealItem++;
		cout << "Zombie count : " << countZombie << "Heal item : " << countHealItem  << endl;

		countTimeHealItem = 0;
	}
	else
		countTimeHealItem += dt;

	*/



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


	//draw text ontop of all our entities and stuff
	//text for gameplay status including HP, playing time, number of zombie, number of heal item
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);


	// check if hero hp equal 0, game over
	if (Globals::heroHealPoint == 0)
	{
		cout << "Game over";

		//Gerate surface from font + string
		//LOAD UP OUR AWESOME FONT
		bool isExit = false;
		while (!isExit)
		{
			
			//adding player name from player input
			//Check for user inputs
			SDL_Event event;
			//loop through all generated input events
			while (SDL_PollEvent(&event)) {
				//check for keyboard events
				if (event.type == SDL_KEYDOWN) {
					//if ESC pressed, exit game
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						// exit while loop
						isExit = true;
					}
				}
			}

			std::stringstream go;
			go << "Game Over! Press escape to exit.";
			TTF_Font* font = TTF_OpenFont("assets/gooddog.otf", 52);	//font location, font size
			SDL_Color textColor = { 250,210,0,0 };//r, g, b a   0-255 each

			SDL_Surface * textSurface = TTF_RenderText_Blended(font, go.str().c_str(), textColor);
			//convert to texture
			SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
			//delete surface
			SDL_FreeSurface(textSurface);

			//text destination
			textDestination->x = (hero->position.x - 300) - Globals::camera.x;
			textDestination->y = (hero->position.y - 50) - Globals::camera.y;
			//get width and height of our texture for the destination
			SDL_QueryTexture(gameOverTexture, NULL, NULL, &textDestination->w, &textDestination->h);

			//draw text ontop of all our entities and stuff
			SDL_RenderCopy(Globals::renderer, gameOverTexture, NULL, textDestination);

			//show the newly drawn up frame of the game
			SDL_RenderPresent(Globals::renderer);

		}

		//exit game
		Globals::gameStateMachine.popState();
		return;
	}

	// if hero can walk out from the maze
	if (hero->isWin == true)
	{
		cout << "Player Win";

		playingTime = (SDL_GetTicks()-startTime)/1000;
		//Gerate surface from font + string
		//LOAD UP OUR AWESOME FONT
		bool isExit = false;
		while (!isExit)
		{

			//adding player name from player input
			//Check for user inputs
			SDL_Event event;
			//loop through all generated input events
			while (SDL_PollEvent(&event)) {
				//check for keyboard events
				if (event.type == SDL_KEYDOWN) {
					//if ESC pressed, exit game
					if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
						// TODO: update rank file
						updateHighScore(playerName, playingTime);

						// exit while loop
						isExit = true;
					}
				}
				if (event.type = SDL_TEXTINPUT)
				{
					playerName += event.text.text;
				}
			}

			TTF_Font* font = TTF_OpenFont("assets/gooddog.otf", 52);	//font location, font size
			SDL_Color textColor = { 250,210,0,0 };//r, g, b a   0-255 each

			SDL_Surface * textSurface = TTF_RenderText_Blended(font, "You Win! Please type your name.", textColor);
			//convert to texture
			SDL_Texture* winTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
			//delete surface
			SDL_FreeSurface(textSurface);

			//text destination
			textDestination->x = (hero->position.x - 300) - Globals::camera.x;
			textDestination->y = (hero->position.y - 50) - Globals::camera.y;
			//get width and height of our texture for the destination
			SDL_QueryTexture(winTexture, NULL, NULL, &textDestination->w, &textDestination->h);

			//draw text ontop of all our entities and stuff
			SDL_RenderCopy(Globals::renderer, winTexture, NULL, textDestination);

			//draw player name
			textSurface = TTF_RenderText_Blended(font, playerName.c_str(), textColor);
			//convert to texture
			winTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
			//delete surface
			SDL_FreeSurface(textSurface);

			//text destination
			textDestination->x = (hero->position.x - 200) - Globals::camera.x;
			textDestination->y = (hero->position.y) - Globals::camera.y;
			//get width and height of our texture for the destination
			SDL_QueryTexture(winTexture, NULL, NULL, &textDestination->w, &textDestination->h);

			//draw text ontop of all our entities and stuff
			SDL_RenderCopy(Globals::renderer, winTexture, NULL, textDestination);

			//show the newly drawn up frame of the game
			SDL_RenderPresent(Globals::renderer);

		}

		//exit game
		Globals::gameStateMachine.popState();
		return;
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
