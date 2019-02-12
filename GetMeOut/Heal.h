#pragma once
#include "Entity.h"
#include "Map.h"
#include <stdlib.h> // rand()

class Heal : public Entity
{
public:
	int destinationRow;	//row posiont of hero in map array
	int destinationColumn; //column posiont of hero in map array

	float drawX, drawY;

	Heal();
	~Heal();

	//overriding
	virtual void update(float dt);
	virtual void draw();

};