#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class World{
public:
	World(sf::Vector2u windSize);
	~World();

	int getBlockSize();

	void respawnApple();

	void update(Snake& player);
	void render(sf::RenderWindow& window);
private:
	sf::Vector2u mWindowSize;
	sf::Vector2i mItem;
	int mBlockSize;

	sf::CircleShape mAppleShape;
	sf::RectangleShape mBounds[4];
};