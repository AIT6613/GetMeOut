#include "MouseHandler.h"


MouseHandler::MouseHandler()
{
}


MouseHandler::~MouseHandler()
{
}

void MouseHandler::update(SDL_Event* event) {
	//CHECK IF USER HAS CLICKED ON OUR HERO
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
		//but was it clicked within the hero region?
		if (event->button.x >= hero->position.x && event->button.x <= hero->position.x + 32
			&& event->button.y >= hero->position.y && event->button.y <= hero->position.y + 32) {
			leftMousePressedDown = true;
		}
	}

	//CHECK IF LEFT MOUSE BUTTON RELEASED
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		leftMousePressedDown = false;
	}

	//if left button pressed AND mouse dragged around
	if (leftMousePressedDown && event->type == SDL_MOUSEMOTION) {
		hero->position.x = event->motion.x;
		hero->position.y = event->motion.y;
	}

}