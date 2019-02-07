#include "Entity.h"

Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}


void Entity::setTexture(const char * fileName, SDL_Renderer* renderer, int optionRemoveBackground, int r, int g, int b)
{
	//load image up as surface
	SDL_Surface* tempSurface = IMG_Load(fileName);

	//set background of texture to be transparent
	//params: surface to change
	//		1 = turn on,  0 = turn off
	//		which colour to user as colour key (SDL_MapRGB will find closest colour match in the surface to set it to)
	SDL_SetColorKey(tempSurface, optionRemoveBackground, SDL_MapRGB(tempSurface->format, r, g, b));

	//next, convert to texture 
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//once we are finished with surface, free up its memory
	SDL_FreeSurface(tempSurface);

	this->renderer = renderer;
}

float Entity::getX()
{
	return position.x;
}

float Entity::getY()
{
	return position.y;
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

void Entity::setSourceRect(float x, float y, float w, float h)
{
	this->sourceRect.x = x;
	this->sourceRect.y = y;
	this->sourceRect.w = w;
	this->sourceRect.h = h;
}



void Entity::update(float dt)
{
	//let subclasses fill these in if they want
}

void Entity::updateMovement(float dt){
	position.x = position.x + (velocity.x * dt);
	position.y = position.y + (velocity.y * dt);
}

void Entity::draw()
{
	//let subclasses fill these in if they want
}


//initialise sattic variables at start of runtime
list<Entity*> *Entity::entities = NULL;