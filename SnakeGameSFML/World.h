#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"

class World{
public:
	World(sf::Vector2u windSize);
	~World();

	int getBlockSize();
	void update(Snake& player);
	void render(sf::RenderWindow& window);
private:
	sf::Vector2u mWindowSize;
	sf::Vector2i mItem;
	int mBlockSize;
	Apple mApple;
	sf::CircleShape mAppleShape;
	sf::RectangleShape mBounds[4];
};