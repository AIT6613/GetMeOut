#include "GameObject.h"

void GameObject::setRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

void GameObject::update(float dt) {
	//nuthin
}

void GameObject::updateMovement(float dt) {
	pos.x = pos.x + (velocity.x*dt);
	pos.y = pos.y + (velocity.y*dt);
}

void GameObject::draw() {
	//nada
}