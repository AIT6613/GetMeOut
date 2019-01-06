#pragma once
#include "GameState.h"
#include "PlayGameState.h"
#include <list>
//#include <SDL_image.h>
#include "Hero.h"
#include "Backgrond.h"
#include "Text.h"
#include "KeyboardHandler.h"
#include "Globals.h"

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

	Animation* heroRun;
	Hero* hero;

	KeyboardHandler keyboardHandle;

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

