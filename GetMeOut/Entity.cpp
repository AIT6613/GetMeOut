#include "Entity.h"



Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Entity::setXY(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Entity::setX(float x)
{
	position.x = x;
}

void Entity::setY(float y)
{
	position.y = y;
}



void Entity::update(float dt)
{
	//let subclasses fill these in if they want
}

void Entity::updateMovement(float dt) {
	position.x = position.x + (velocity.x * dt);
	position.y = position.y + (velocity.y * dt);
}

void Entity::draw()
{
	//let subclasses fill these in if they want
}
