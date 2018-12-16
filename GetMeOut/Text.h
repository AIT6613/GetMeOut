#pragma once
#include "Entity.h"

class Text : public Entity
{
private:
	float w, h;


public:
	Text();
	~Text();
	void setWH(float w, float h);

	virtual void draw();

};