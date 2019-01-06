#pragma once
#include "Entity.h"
class Dirt :
	public Entity
{
private:
	float drawX;
	float drawY;

public:
	Dirt();
	~Dirt();

	virtual void draw();

};

