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
	return (!mSnakeBody.empty() ? mSnakeBody.front().position : sf::Vector2i(1,1));
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
		if (head.position.x == neck.position.x)
		{
			retVal = (head.position.y > neck.position.y ? Direction::Down: Direction::Up);
		}
		else if(head.position.y == neck.position.y)
		{
			retVal = (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
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
		std::cout << "Extend " << preLastTailSegment.position.x << " " << lastTailSegment.position.x << std::endl;
		if (preLastTailSegment.position.x == lastTailSegment.position.x) 
		{
			if (preLastTailSegment.position.y > lastTailSegment.position.y)
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x, lastTailSegment.position.y - 1));
				std::cout << "Extend " << mSnakeBody.size();
			}
			else 
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x, lastTailSegment.position.y + 1));
			}
		}
		else //(preLastTailSegment.position.y == lastTailSegment.position.y)
		{
			if (preLastTailSegment.position.x > lastTailSegment.position.x)
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x-1, lastTailSegment.position.y));
			}
			else
			{
				mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x+1, lastTailSegment.position.y));
			}
		}
	}
	else
	{
		switch (getDirection()) 
		{
		case Direction::Down:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x, lastTailSegment.position.y - 1));
			break;

		case Direction::Up:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x, lastTailSegment.position.y + 1));
			break;

		case Direction::Left:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x+1, lastTailSegment.position.y));
			break;

		case Direction::Right:
			mSnakeBody.push_back(SnakeSegment(lastTailSegment.position.x-1, lastTailSegment.position.y));
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
	mSpeed = 15;
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
		if (head.position == itr->position)
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
		*itr = *(itr - 1);
	}
	switch (getDirection())
	{
	case Direction::Down:
		mSnakeBody[0].position.y = mSnakeBody[0].position.y + 1;
		break;

	case Direction::Up:
		mSnakeBody[0].position.y = mSnakeBody[0].position.y - 1;
		break;

	case Direction::Left:
		mSnakeBody[0].position.x = mSnakeBody[0].position.x - 1;
		break;

	case Direction::Right:
		mSnakeBody[0].position.x = mSnakeBody[0].position.x + 1;
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
	mBodyRect.setFillColor(sf::Color::Blue);
	mBodyRect.setPosition(snakeHead->position.x*mSize, snakeHead->position.y*mSize);
	window.draw(mBodyRect);

	mBodyRect.setFillColor(sf::Color::Green);
	for (auto itr = mSnakeBody.begin() + 1; itr != mSnakeBody.end(); ++itr) 
	{
		mBodyRect.setPosition(itr->position.x*mSize, itr->position.y*mSize);
		window.draw(mBodyRect);
	}

}