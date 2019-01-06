#include "CameraManager.h"


void CameraManager::update() {
	if (target != NULL) {
		Globals::camera.x = target->position.x - Globals::screenWidth / 2;
		Globals::camera.y = target->position.y - Globals::screenHeight / 2;
	}
}
