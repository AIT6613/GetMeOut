#pragma once
#include "GameState.h"
#include "KeyboardHandler.h"
#include "Globals.h"
#include "SoundManager.h"
#include <SDL_ttf.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class HighScoreState :
	public GameState
{
public:

	// for text
	TTF_Font* font;
	SDL_Color textColor;
	SDL_Surface * textSurface;
	SDL_Texture* textTexture;
	SDL_Rect* textDestination;

	int textXpos;
	int textYpos;
	string textString;

	string** scoreBoard;

	int time_target;
	int hour;
	int minute;
	int second;

	HighScoreState();
	~HighScoreState();

	//to help with working out deltaTime
	Uint32 lastUpdate = SDL_GetTicks();
	float dt = 0;

	//override those abstract methods inherited
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() {
		return "highScoreState";
	}
};



