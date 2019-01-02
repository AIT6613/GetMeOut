#pragma once
#include "Entity.h"
class Wall :
	public Entity
{
public:
	Wall();
	~Wall();

	virtual void draw();
};

