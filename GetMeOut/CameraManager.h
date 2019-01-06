#pragma once
#include "Entity.h"
#include "Globals.h"

class CameraManager
{
public:
	//the game thing the camera follows
	Entity* target;

	void update();
};