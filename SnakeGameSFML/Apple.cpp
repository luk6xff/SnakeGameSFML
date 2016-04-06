#include "Apple.h"




Apple::Apple(int posX, int posY, const sf::Texture & texture, int appleSize) :Fruit(posX, posY,appleSize, texture),mAppleShape()
{
}

Apple::Apple(int posX, int posY, int appleSize): Fruit(posX, posY,appleSize), mAppleShape()
{
	setPosition(posX,posY);
	mAppleShape.setFillColor(sf::Color::Red); //default value
	mAppleShape.setPosition(getPosition().x*getSize(), getPosition().y*getSize());
	mAppleShape.setRadius(getSize()/2);
	srand(time(nullptr));
}

Apple::~Apple()
{
}

void Apple::update()
{
	mAppleShape.setPosition(getPosition().x*getSize(), getPosition().y*getSize());
}

void Apple::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mAppleShape, states);
}

void Apple::setColor(sf::Color color)
{
	mAppleShape.setFillColor(color);
}

void Apple::putApple(const sf::Vector2u& windowSize)
{
		int maxX = (windowSize.x / getSize()) - 2;
		int maxY = (windowSize.y / getSize()) - 2;
		auto mItem = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
		setPosition(mItem.x,mItem.y);
		mAppleShape.setPosition(getPosition().x*getSize(), getPosition().y*getSize());
		mAppleShape.setRadius(getSize()/2);
	
}
