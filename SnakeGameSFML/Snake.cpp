#include "Snake.h"
#include <iostream>

Snake::Snake(int blockSize):mBodyRect(){
	mSize = blockSize;
	mBodyRect.setSize(sf::Vector2f(mSize - 1, mSize - 1));
	reset();
}

Snake::~Snake()
{
}

void Snake::setDirection(Direction dir)
{ 
	mDir = dir; 
}

Direction Snake::getDirection()
{ 
	return mDir; 
}

int Snake::getSpeed()
{ 
	return mSpeed; 
}

sf::Vector2i Snake::getPosition()
{
	return (!mSnakeBody.empty() ? static_cast<sf::Vector2i>(mSnakeBody.front().getPosition()) : sf::Vector2i(1,1));
}

int Snake::getLives()
{ 
	return mLives; 
}

int Snake::getScore()
{ 
	return mScore;
}

void Snake::increaseScore()
{
	mScore++;
}

bool Snake::hasLost()
{ 
	return mLost; 
}

void Snake::lose()
{ 
	mLost = true; 
}

void Snake::toggleLost()
{ 
	mLost = !mLost; 
}


Direction Snake::getPhysicalDirection()
{
	Direction retVal= Direction::None;
	if (mSnakeBody.size() > 1)
	{
		SnakeSegment& head = mSnakeBody[0];
		SnakeSegment& neck = mSnakeBody[1];
		if (head.getPosition().x == neck.getPosition().x)
		{
			retVal = (head.getPosition().y > neck.getPosition().y ? Direction::Down: Direction::Up);
		}
		else if(head.getPosition().y == neck.getPosition().y)
		{
			retVal = (head.getPosition().x > neck.getPosition().x ? Direction::Right : Direction::Left);
		}
	}
	return retVal;
}

void Snake::extend()
{

	if (mSnakeBody.empty())
	{
		return;
	}
	SnakeSegment &lastTailSegment = mSnakeBody[mSnakeBody.size() - 1];//mSnakeBody.back();
	if (mSnakeBody.size() > 1) 
	{
		SnakeSegment &preLastTailSegment = mSnakeBody[mSnakeBody.size()-2];
		//std::cout << "Extend " << preLastTailSegment.getPosition().x << " " << lastTailSegment.getPosition().x << std::endl;
		if (preLastTailSegment.getPosition().x == lastTailSegment.getPosition().x) 
		{
			if (preLastTailSegment.getPosition().y > lastTailSegment.getPosition().y)
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x, lastTailSegment.getPosition().y - 1));
				//std::cout << "Extend " << mSnakeBody.size();
			}
			else 
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x, lastTailSegment.getPosition().y + 1));
			}
		}
		else //(preLastTailSegment.getPosition().y == lastTailSegment.getPosition().y)
		{
			if (preLastTailSegment.getPosition().x > lastTailSegment.getPosition().x)
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x-1, lastTailSegment.getPosition().y));
			}
			else
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x+1, lastTailSegment.getPosition().y));
			}
		}
	}
	else
	{
		switch (getDirection()) 
		{
		case Direction::Down:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x, lastTailSegment.getPosition().y - 1));
			break;

		case Direction::Up:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x, lastTailSegment.getPosition().y + 1));
			break;

		case Direction::Left:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x+1, lastTailSegment.getPosition().y));
			break;

		case Direction::Right:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.getPosition().x-1, lastTailSegment.getPosition().y));
			break;
		
		default:
			break;
		}
	}
}

void Snake::reset()
{
	mSnakeBody.clear();
	mSnakeBody.push_back(SnakeSegment(5, 7));
	mSnakeBody.push_back(SnakeSegment(5, 6));
	mSnakeBody.push_back(SnakeSegment(5, 5));
	setDirection(Direction::None); 
	mSpeed = 10;
	mLives = 3;
	mScore = 0;
	mLost = false;
}

void Snake::checkCollision()
{
	if (mSnakeBody.empty() || mDir == Direction::None|| mSnakeBody.size()<5)
		return;
	SnakeSegment &head = mSnakeBody.front();
	for (auto itr = mSnakeBody.begin() + 1; itr != mSnakeBody.end(); ++itr)
	{
		if (head.getPosition() == itr->getPosition())
		{
			cut(mSnakeBody.end() - itr);
			break;
		}
	}


}

void Snake::move()
{
	for (auto itr = mSnakeBody.end()-1; itr != mSnakeBody.begin();--itr)
	{
		itr->setPosition((itr - 1)->getPosition());
	}
	switch (getDirection())
	{
	case Direction::Down:
		mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x, mSnakeBody[0].getPosition().y + 1);
		break;

	case Direction::Up:
		mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x, mSnakeBody[0].getPosition().y - 1);
		break;

	case Direction::Left:
		mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x - 1, mSnakeBody[0].getPosition().y);
		break;

	case Direction::Right:
		mSnakeBody[0].setPosition(mSnakeBody[0].getPosition().x + 1, mSnakeBody[0].getPosition().y);
		break;

	default:
		break;
	}

}

void Snake::tick()
{
	if (mSnakeBody.empty()|| mDir == Direction::None)
		return;
	checkCollision();
	move();
}

void Snake::cut(int segments)
{
	if (mSnakeBody.size() <= segments)
	{
		return;
	}
	mSnakeBody.erase(mSnakeBody.end()-segments, mSnakeBody.end());
	--mLives;
	if (mLives == 0) {
		lose();
	}
}

void Snake::render(sf::RenderWindow& window)
{
	if (mSnakeBody.empty())
	{
		return;
	}

	auto snakeHead = mSnakeBody.begin();
	snakeHead->setColor(sf::Color::Blue);
	snakeHead->update();
	window.draw(*snakeHead);
	for (auto itr = mSnakeBody.begin() + 1; itr != mSnakeBody.end(); ++itr) 
	{
		itr->setColor(sf::Color::Green);
		itr->update();
		window.draw(*itr);
	}

}

