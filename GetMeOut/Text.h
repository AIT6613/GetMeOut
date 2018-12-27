#pragma once
#include "Entity.h"

class Text : public Entity
{
private:
	//float w, h;


public:
	Text();
	~Text();
	

	virtual void draw();
};