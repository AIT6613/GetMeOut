#pragma once
#include "Entity.h"
#include "Map.h"
#include <iostream>

using namespace std;

class Wall :
	public Entity
{
private:
	float drawX;
	float drawY;

public:
	Wall();
	~Wall();

	virtual void draw();
};

 