#pragma once
#include "GameState.h"
#include "PlayGameState.h"
#include "HighScoreState.h"
#include <list>
//#include <SDL_image.h>
#include "Hero.h"
#include "Backgrond.h"
#include "Text.h"
#include "KeyboardHandler.h"
#include "Globals.h"
#include "SoundManager.h"

class MenuGameState :
	public GameState
{
public:
	int menuPointer = 1;

	list<Entity*> entities;

	Backgrond* titleBackground;
	Text* gameTitle;
	Text* menuPlayGame;
	Text* menuTopRank;
	Text* menuExit;

	Animation* heroRunAnimation;
	Hero* hero;

	KeyboardHandler keyboardHandle;

	// for text
	TTF_Font* font;
	SDL_Color textColor;
	SDL_Surface * textSurface;
	SDL_Texture* textTexture;
	SDL_Rect* textDestination;

	//to help with working out deltaTime
	Uint32 lastUpdate = SDL_GetTicks();
	float dt = 0;


	MenuGameState();
	~MenuGameState();

	//override those abstract methods inherited
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() {
		return "menuState";
	}
};

