#pragma once
#include <iostream>
#include "GameState.h"
#include <list>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Hero.h"
#include "Wall.h"
#include "Dirt.h"
#include "Map.h"
#include "Zombie.h"
#include "KeyboardHandler.h"
#include "GameControllerHandler.h"
#include "MouseHandler.h"
#include "Globals.h"
#include "CameraManager.h"
#include "MenuGameState.h"
#include "Heal.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class PlayGameState :
	public GameState
{

public:
	Animation* heroRunAnimation;
	Animation* zombieAnimation;
	Hero* hero;
	Wall* wall;
	Dirt* dirt;
	Map* map;
	Zombie* zombie;
	Heal* heal;

	SDL_Surface* zombieSurface;
	SDL_Texture* textTexture;
	SDL_Rect* textDestination;
	TTF_Font* font;

	list<Entity*> entities;

	
	KeyboardHandler keyboardHandler;
	MouseHandler mouseHandler;
	GameControllerHandler controllerHandler;

	CameraManager cameraManager;

	float countTimeZombie = 0, countTimeHealItem = 0;
	

	Uint32 lastUpdate; //last sdl_getTicks();
	int startTime;
	float dt = 0;


	bool isPutZombie = false;
	int randX, randY;
	int countZombie = 0;
	int countHealItem = 0;
	string playerName = "";
	int playingTime = 0;




	PlayGameState();
	~PlayGameState();

	void updateHighScore(string playerName, int playingTime);

	//override those abstract methods inherited
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() {
		return "playState";
	}
};

