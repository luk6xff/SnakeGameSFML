#include "SnakeSegment.h"





SnakeSegment::~SnakeSegment()
{
}


SnakeSegment::SnakeSegment(int x, int y)
{
	setPosition(x, y);
}
/*
const sf::Vector2i & SnakeSegment::getPosition()
{
	return static_cast<sf::Vector2i>(getWorldPosition());
}

void SnakeSegment::setPosition(const sf::Vector2i & position)
{
	sf::Vector2f realPosition = static_cast<sf::Vector2f>(position);
	Entity::setPosition(realPosition);
}

void SnakeSegment::setPosition(int x, int y)
{
	setPosition(sf::Vector2i(x, y));
}
*/
void SnakeSegment::update()
{

}

void SnakeSegment::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

}
