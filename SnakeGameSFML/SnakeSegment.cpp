#include "SnakeSegment.h"
#include<iostream>



SnakeSegment::SnakeSegment(int x, int y,const sf::Texture& texture, int segmentSize):Entity(texture), mSegmentSize(segmentSize), mSegmentRect()
{
	setPosition(x, y);
	mSegmentRect.setSize(sf::Vector2f(mSegmentSize - 1, mSegmentSize - 1));
	
}

SnakeSegment::SnakeSegment(int x, int y, int segmentSize) : Entity(), mSegmentSize(segmentSize)
{
	setPosition(x, y);
	mSegmentRect.setSize(sf::Vector2f(mSegmentSize - 1, mSegmentSize - 1));
}

SnakeSegment::~SnakeSegment()
{
}


void SnakeSegment::update()
{
	mSegmentRect.setPosition(getPosition().x*mSegmentSize,getPosition().y*mSegmentSize);
}

void SnakeSegment::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSegmentRect,states);
	//std::cout << "HERE";
}

void SnakeSegment::setColor(sf::Color color)
{
	mSegmentRect.setFillColor(color);
}
