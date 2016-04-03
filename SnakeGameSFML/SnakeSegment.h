#pragma once
#include "Entity.h"

#include <vector>

class  SnakeSegment :public Entity {
public:
	explicit SnakeSegment(int x, int y);

	//const sf::Vector2i& getPosition();
    //void setPosition(const sf::Vector2i& position);
	//void setPosition(int x, int y);

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~SnakeSegment();

private:
	sf::Vector2i position;
};