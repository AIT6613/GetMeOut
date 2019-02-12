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

	list<Entity*> entities;

	KeyboardHandler keyboardHandler;
	MouseHandler mouseHandler;
	GameControllerHandler controllerHandler;

	CameraManager cameraManager;

	float countTimeZombie = 0, countTimeHealItem = 0;
	int heroHealPoint, damagePoint, healPoint, zombieGenTime, healItemGenTime;

	Uint32 lastUpdate; //last sdl_getTicks();
	float dt = 0;


	bool isPutZombie = false;
	int randX, randY;
	int countZombie = 0;




	PlayGameState();
	~PlayGameState();

	//override those abstract methods inherited
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() {
		return "playState";
	}
};

