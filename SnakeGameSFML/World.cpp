#include "World.h"
#include <iostream>
World::World(sf::Vector2u windSize, int blockSize):mBlockSize(blockSize),mApple(0,0, mBlockSize), mSnake(mBlockSize){
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
	std::cout << player.getPosition().x<<" ";
	std::cout << player.getPosition().y << std:: endl;
	std::cout << "APP: "<< mApple.getPosition().x << " ";
	std::cout << mApple.getPosition().y << std::endl;
	if(player.getPosition() == mApple.getPosition())
	{
		player.extend();
		player.increaseScore();
		mApple.putApple(mWindowSize);
		std::cout << "increased";
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