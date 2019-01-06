#pragma once
#include <string>
#include <iostream>

using namespace std;

class GameState
{
public:
	GameState();
	~GameState();

	//abstract functions
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual string getStateID() = 0;
};

