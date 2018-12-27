#include "Entity.h"

Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}


void Entity::setTexture(const char * fileName, SDL_Renderer* renderer)
{
	//load image up as surface
	SDL_Surface* tempSurface = IMG_Load(fileName);
	//next, convert to texture 
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(tempSurface);

	this->renderer = renderer;
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

void Entity::setWH(float w, float h)
{
	this->w = w;
	this->h = h;
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
