#include "HighScoreState.h"


HighScoreState::HighScoreState()
{

	//setup input handlers
	KeyboardHandler keyboardHandler;
}


HighScoreState::~HighScoreState()
{
	delete font;
	delete textSurface;
	delete textTexture;
	delete textDestination;

}

void HighScoreState::update() {

	
	
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

	}

}

void HighScoreState::render() {

	//clear the previous draw
	SDL_RenderClear(Globals::renderer);

	//show menu
	//clear out old text texture
	if (textTexture != NULL)
		SDL_DestroyTexture(textTexture);


	//show score board for level 1
	textXpos = 50;
	textYpos = 50;

	//LOAD UP OUR AWESOME FONT
	font = TTF_OpenFont("assets/gooddog.otf", 48);	//font location, font size
	textColor = { 250,210,0,0 };//r, g, b a   0-255 each
	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "High score Level 1", textColor);
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

	
	fstream level1File("assets/HighScoreLevel1.txt");

	//create new row for array
	scoreBoard = new string*[10];
	for (int i = 0; i < 10; ++i)
		//crate new column for array
		scoreBoard[i] = new string[2];

	//read score board from file
	for (int i = 0; i < 10; i++) {
		//get string line from file
		//read 2 line for one record,
		//first line is name
		if (getline(level1File, textString))
		{
			scoreBoard[i][0] = textString.c_str();
		}
		else
		{
			exit;
		}
		//second line is score
		if (getline(level1File, textString))
		{
			scoreBoard[i][1] = textString.c_str();
		}

	}
	level1File.close();

	//show score board
	for (int i = 0; i < 10; i++)
	{
		if (scoreBoard[i][0].c_str() == "")
		{
			exit;
		}

		//calculate to time format
		//double s(fabs((SDL_GetTicks() - startTime) / 1000));
		time_target = atoi(scoreBoard[i][1].c_str());
		hour = time_target / 3600;
		second = time_target % 3600;
		minute = second / 60;
		second = (time_target - (hour * 3600)) % 60;

		std::stringstream lv1;
		lv1 << i + 1 << ". " << scoreBoard[i][0].c_str() << "  " << hour << ":" << minute << ":" << second;
		//LOAD UP OUR AWESOME FONT
		font = TTF_OpenFont("assets/gooddog.otf", 32);	//font location, font size
		textColor = { 250,210,0,0 };//r, g, b a   0-255 each
		//Gerate surface from font + string
		textSurface = TTF_RenderText_Blended(font, lv1.str().c_str(), textColor);
		//convert to texture
		textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
		//delete surface
		SDL_FreeSurface(textSurface);
		//text destination
		textDestination = new SDL_Rect();
		textDestination->x = textXpos + 50;
		textYpos += 50;
		textDestination->y = textYpos;
		//get width and height of our texture for the destination
		SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
		//draw text ontop of all our entities and stuff
		SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);
	}

	//show score board level 2
	textXpos = 420;
	textYpos = 50;

	//LOAD UP OUR AWESOME FONT
	font = TTF_OpenFont("assets/gooddog.otf", 48);	//font location, font size
	textColor = { 250,210,0,0 };//r, g, b a   0-255 each
	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "High score Level 2", textColor);
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


	fstream level2File("assets/HighScoreLevel2.txt");

	//create new row for array
	scoreBoard = new string*[10];
	for (int i = 0; i < 10; ++i)
		//crate new column for array
		scoreBoard[i] = new string[2];

	//read score board from file
	for (int i = 0; i < 10; i++) {
		//get string line from file
		//read 2 line for one record,
		//first line is name
		if (getline(level2File, textString))
		{
			scoreBoard[i][0] = textString.c_str();
		}
		else
		{
			exit;
		}
		//second line is score
		if (getline(level2File, textString))
		{
			scoreBoard[i][1] = textString.c_str();
		}

	}
	level2File.close();

	//show score board
	for (int i = 0; i < 10; i++)
	{
		if (scoreBoard[i][0].c_str() == "")
		{
			exit;
		}

		//calculate to time format
		//double s(fabs((SDL_GetTicks() - startTime) / 1000));
		time_target = atoi(scoreBoard[i][1].c_str());
		hour = time_target / 3600;
		second = time_target % 3600;
		minute = second / 60;
		second = (time_target - (hour * 3600)) % 60;

		std::stringstream lv2;
		lv2 << i + 1 << ". " << scoreBoard[i][0].c_str() << "  " << hour << ":" << minute << ":" << second;
		//LOAD UP OUR AWESOME FONT
		font = TTF_OpenFont("assets/gooddog.otf", 32);	//font location, font size
		textColor = { 250,210,0,0 };//r, g, b a   0-255 each
		//Gerate surface from font + string
		textSurface = TTF_RenderText_Blended(font, lv2.str().c_str(), textColor);
		//convert to texture
		textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
		//delete surface
		SDL_FreeSurface(textSurface);
		//text destination
		textDestination = new SDL_Rect();
		textDestination->x = textXpos+50;
		textYpos += 50;
		textDestination->y = textYpos;
		//get width and height of our texture for the destination
		SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
		//draw text ontop of all our entities and stuff
		SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);
	}

	//show how to exit high score screen
	//LOAD UP OUR AWESOME FONT
	font = TTF_OpenFont("assets/gooddog.otf", 32);	//font location, font size
	textColor = { 250,210,0,0 };//r, g, b a   0-255 each
	//Gerate surface from font + string
	textSurface = TTF_RenderText_Blended(font, "Press ESC to exit", textColor);
	//convert to texture
	textTexture = SDL_CreateTextureFromSurface(Globals::renderer, textSurface);
	//delete surface
	SDL_FreeSurface(textSurface);
	//text destination
	textDestination = new SDL_Rect();
	textDestination->x = 300;
	textDestination->y = 600;
	//get width and height of our texture for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination->w, &textDestination->h);
	//draw text ontop of all our entities and stuff
	SDL_RenderCopy(Globals::renderer, textTexture, NULL, textDestination);


	//show the newly drawn up frame of the game
	SDL_RenderPresent(Globals::renderer);

}


bool HighScoreState::onEnter() {
	cout << "Entering menu state" << endl;
	return true;
}
bool HighScoreState::onExit() {
	cout << "Exiting menu state" << endl;
	return true;
}
