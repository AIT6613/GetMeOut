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

void Entity::setTexture(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect) {
	this->texture = texture;
	this->sourceRect = sourceRect;
	this->destinationRect = destinationRect;

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

}
