#pragma once
#include "Entity.h"

class TitleBackgrond : public Entity
{
private:
	float w, h;


public:
	TitleBackgrond();
	~TitleBackgrond();
	void setWH(float w, float h);

	virtual void draw();

};

