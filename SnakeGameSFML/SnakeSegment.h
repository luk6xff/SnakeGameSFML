#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"

#include <vector>

class  SnakeSegment :public Entity {
public:
	explicit SnakeSegment(int x, int y, const sf::Texture& texture, int segmentSize=16);
	SnakeSegment(int x, int y,int segmentSize= 16);

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setColor(sf::Color color);

	~SnakeSegment();

private:
	int mSegmentSize;
	sf::RectangleShape mSegmentRect; // Shape used in rendering
};