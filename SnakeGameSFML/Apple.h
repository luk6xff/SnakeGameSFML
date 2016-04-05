#pragma once
#include "Fruit.h"

#include <SFML/Graphics.hpp>
class Apple :
	public Fruit
{
public:
	Apple(int posX, int posY, const sf::Texture& texture,int appleSize =16);
	explicit Apple(int x, int y, int appleSize = 16);
	~Apple();

	void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setColor(sf::Color color);
	void putApple(const sf::Vector2u& windowSize);
private:
	sf::CircleShape mAppleShape;
};

