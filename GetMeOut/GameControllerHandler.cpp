#include "GameControllerHandler.h"


GameControllerHandler::GameControllerHandler()
{
	//see if any joysticks(include gamepads/steering wheels etc) are connected
	int numJoysticks = SDL_NumJoysticks();

	//connected joystick ids start at 0 and go up
	for (int joystickID = 0; joystickID < numJoysticks; joystickID++) {
		//check to see if this controller is a game controller (not a steering wheel or other weird device)
		if (SDL_IsGameController(joystickID)) {
			//if it is, sweet, lets use it
			controller = SDL_GameControllerOpen(joystickID);
			//in this example we only care about 1 controller, so we'll exit the loop. 
			//Keep going and storing controllers if you want a local multiplayer game
			break;
		}
	}


}


GameControllerHandler::~GameControllerHandler()
{
	//close off controller if we have one
	if (controller != NULL)
		SDL_GameControllerClose(controller);
}


void GameControllerHandler::update(SDL_Event* event) {
	//if controller not null and not detached
	if (controller != NULL && SDL_GameControllerGetAttached(controller)) {
		//we'll get the joystickID associated with our gamecontroller
		SDL_JoystickID joystickID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
		//check if this sdl event was from this controller
		if (event->cdevice.which == joystickID) {
			//lets check for events now that might happen

			//IF controller was removed
			if (event->type == SDL_CONTROLLERDEVICEREMOVED) {
				//close controller and set to null
				SDL_GameControllerClose(controller);
				controller = NULL;
				//exit function, cant do the rest of this code if the controller is not connected
				return;
			}

			//IF was button event
			if (event->type == SDL_CONTROLLERBUTTONDOWN) {
				//check individual buttons
				//NOTE: Game controller class treats all gamecontrollers like Xbox controllers
				//so we have buttons a b x y. So if I press the circle button on a ps4, we'll be calling in B
				//A button
				if (event->cbutton.button == SDL_CONTROLLER_BUTTON_A) {
					//reset players position
					hero->position.x = 200;
					hero->position.y = 200;
				}
				//add buttons B, X, Y etc if necessary
			}

			//reset players velocity
			hero->velocity.x = 0;
			hero->velocity.y = 0;

			//Check left stick X and Y axis
			Sint16 axisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
			Sint16 axisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
			//we should cater for stick 'deadzone', because resting values in the middle wont always be zero
			int deadzone = 10000;

			//check if moving stick left OR holding left on DPAD
			if (axisX < -deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
				hero->velocity.x = -80;
			//check for right on the stick or DPAD right
			if (axisX > deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
				hero->velocity.x = 80;
			//up
			if (axisY < -deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP))
				hero->velocity.y = -80;
			//down
			if (axisY > deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
				hero->velocity.y = 80;

		}
	}
}