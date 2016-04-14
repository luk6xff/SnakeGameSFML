#pragma once
#include <SFML/Graphics.hpp>

#include "SnakeSegment.h"

#include <vector>

using SnakeBodyContainer = std::vector<SnakeSegment>;
enum class Direction{ None, Up, Down, Left, Right };

class Snake{
public:
	Snake(int blockSize);
	~Snake();

	// Helper methods.
	void setDirection(Direction dir);
	Direction getDirection();
	int getSpeed();
	sf::Vector2f getPosition();
	int getLives();
	int getScore();
	void increaseScore();
	bool hasLost();

	void lose(); // Handle losing here.
	void toggleLost();

	Direction getPhysicalDirection();

	void extend(); // Grow the snake.
	void reset(); // Reset to starting position().

	void move(); // Movement method.
	void update(); // Update method.
	void cut(int segments); // Method for cutting snake.
	void render(sf::RenderWindow& lWindow);
private:
	void checkCollision(); // Checking collisions.

	SnakeBodyContainer mSnakeBody; // Segment vector.
	int mSize; // Size of the graphics.
	Direction mDir; // Current direction.
	int mSpeed; // Speed of the snake.
	int mLives; // Lives.
	int mScore; // Score.
	bool mLost; // Losing state.
	sf::RectangleShape mBodyRect; // Shape used in rendering.
};