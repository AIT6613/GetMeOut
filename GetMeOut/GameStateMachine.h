#pragma once
#include "GameState.h"
#include <vector> //for our stack structure. whats the diff between list and vector? vector stores things in ram next to each other, list is all separate
#include <iostream>

using namespace std;

class GameStateMachine
{
public:
	//our stack of gamestates
	vector<GameState*> gameStates;

	GameStateMachine();
	~GameStateMachine();

	//state management
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
	void clearAll();

	void update();
	void render();


};

