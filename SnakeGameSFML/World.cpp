#include "World.h"
#include <iostream>
World::World(sf::Vector2u windSize, int blockSize):mBlockSize(blockSize),mApple(0,0, mBlockSize), mSnake(mBlockSize)
{
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


bool World::setupEventHandling(StateType stateType, EventManager * evManager)
{
	evManager->addCallback(stateType, "ChangeDirection", &Snake::handleButton, &mSnake);
	return false;
}

int World::getBlockSize()
{ 
	return mBlockSize; 
}

void World::update()
{
	/*std::cout << mSnake.getPosition().x<<" ";
	std::cout << mSnake.getPosition().y << std:: endl;
	std::cout << "APP: "<< mApple.getPosition().x << " ";
	std::cout << mApple.getPosition().y << std::endl;
	*/
	mSnake.update();
	if(mSnake.getPosition() == mApple.getPosition())
	{
		mSnake.extend();
		mSnake.increaseScore();
		mApple.putApple(mWindowSize);
		std::cout << "increased";
	}

	int gridSizeX = mWindowSize.x / mBlockSize;
	int gridSizeY = mWindowSize.y / mBlockSize;

	if(mSnake.getPosition().x <= 0 ||
		mSnake.getPosition().y <= 0 ||
		mSnake.getPosition().x >= gridSizeX - 1 ||
		mSnake.getPosition().y >= gridSizeY - 1)
	{
		mSnake.lose();
	}
	if (mSnake.hasLost()) 
	{
		mSnake.reset();
	}
}

void World::render(sf::RenderWindow& window)
{
	for(int i = 0; i < 4; ++i)
	{
		window.draw(mBounds[i]);
	}
	window.draw(mApple);
	mSnake.render(window);
}