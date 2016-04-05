#include "World.h"

World::World(sf::Vector2u windSize):mApple(30,30){
	mBlockSize = 16;

	mWindowSize = windSize;
	mApple.putApple(mWindowSize);
	mApple.setColor(sf::Color::Red);

	for(int i = 0; i < 4; ++i){
		mBounds[i].setFillColor(sf::Color(150,0,0));
		if(!((i + 1) % 2)){
			mBounds[i].setSize(sf::Vector2f(mWindowSize.x, mBlockSize));
		} else {
			mBounds[i].setSize(sf::Vector2f(mBlockSize, mWindowSize.y));
		}
		if(i < 2){
			mBounds[i].setPosition(0,0);
		} else {
			mBounds[i].setOrigin(mBounds[i].getSize());
			mBounds[i].setPosition(sf::Vector2f(mWindowSize));
		}
	}
}

World::~World(){}

int World::getBlockSize(){ return mBlockSize; }

void World::update(Snake& player){
	if(player.getPosition() == static_cast<sf::Vector2i>(mApple.getPosition())){
		player.extend();
		player.increaseScore();
		mApple.putApple(mWindowSize);
	}

	int gridSize_x = mWindowSize.x / mBlockSize;
	int gridSize_y = mWindowSize.y / mBlockSize;

	if(player.getPosition().x <= 0 ||
		player.getPosition().y <= 0 ||
		player.getPosition().x >= gridSize_x - 1 ||
		player.getPosition().y >= gridSize_y - 1)
	{
			player.lose();
	}
}

void World::render(sf::RenderWindow& window){
	for(int i = 0; i < 4; ++i){
		window.draw(mBounds[i]);
	}
	window.draw(mApple);
}