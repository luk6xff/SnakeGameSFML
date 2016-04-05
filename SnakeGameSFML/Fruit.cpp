#include "Fruit.h"





Fruit::Fruit(int posX, int posY, int size,const sf::Texture & texture):Entity(texture), mSize(size)
{
	setPosition(posX, posY);
}

Fruit::Fruit(int posX, int posY, int size):mSize(size)
{
	setPosition(posX, posY);
}

Fruit::~Fruit()
{
}

void Fruit::setSize(int size)
{
	mSize = size;
}

int Fruit::getSize()
{
	return mSize;
}

void Fruit::setName(const std::string & name)
{
	mName = name;
}

const std::string & Fruit::getName()
{
	return mName;
}
