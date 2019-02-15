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


	//setup input handlers
	KeyboardHandler keyboardHandler;
	keyboardHandler.hero = hero;
}


MenuGameState::~MenuGameState()
{
	//cleanup dynamic memory
	delete titleBackground;
	delete gameTitle;


	//Loop through entities
	for (Entity* e : entities) {
		//delete and disalocate memory
		delete e;
	}

}

void MenuGameState::update() {

	//TIME MANAGEMENT, work out Delta Time (time since last rendering)
	Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
	//convert this to milliseconds over 1 whole second(dt is a fraction)
	dt = timeDiff / 1000.0;	//e.g 200 is now 0.2
   //update lastUpdate, so DT is calculated correctly next loop
	lastUpdate = SDL_GetTicks();

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
			//check press button is 1
			if (event.key.keysym.scancode == SDL_SCANCODE_1) {
				//set level for game play
				Globals::gamePlayLevel = 1;
				//start game
				Globals::gameStateMachine.pushState(new PlayGameState());
			}
			//check press button is 2
			if (event.key.keysym.scancode == SDL_SCANCODE_2) {
				//set level for game play
				Globals::gamePlayLevel = 2;
				//start game
				Globals::gameStateMachine.pushState(new PlayGameState());
			}
			//check press button is s
			if (event.key.keysym.scancode == SDL_SCANCODE_S) {
				//open high score screen
				Globals::gameStateMachine.pushState(new HighScoreState());
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

	//show menu
	//clear out old text texture
	if (textTexture != NULL)
		SDL_DestroyTexture(textTexture);

	int textXpos = 250;
	int textYpos = 300;


	//LOAD UP OUR AWESOME FONT
	font = TTF_OpenFont("assets/gooddog.otf", 36);	//font location, font size
	textColor = { 0,0,0,0 };//r, g, b a   0-255 each
	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "Play game level 1 (press 1)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos+2;
	textDestination->y = textYpos+2;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);


	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "Play game level 2 (press 2)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos + 2;
	textDestination->y = textYpos + 52;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);

	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "High score (press s)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos + 2;
	textDestination->y = textYpos + 102;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);

	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "Exit (press escape)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos + 2;
	textDestination->y = textYpos + 152;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);



	//LOAD UP OUR AWESOME FONT
	font = TTF_OpenFont("assets/gooddog.otf", 36);	//font location, font size
	textColor = { 250,210,0,0 };//r, g, b a   0-255 each
	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "Play game level 1 (press 1)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos;
	textDestination->y = textYpos;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);


	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "Play game level 2 (press 2)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos;
	textDestination->y = textYpos + 50;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);

	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "High score (press s)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos;
	textDestination->y = textYpos + 100;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);

	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "Exit (press escape)", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = textXpos;
	textDestination->y = textYpos + 150;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);


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
