#pragma once
#include "Entity.h"
#include <string>
class Fruit : 
	public Entity
{
public:
	Fruit(int posX,int posY,int mSize, const sf::Texture& texture);
	Fruit(int posX, int posY, int mSize);
	virtual ~Fruit();

public:
	void setSize(int size);
	int getSize();
	void setName(const std::string& name);
	const std::string& getName();
protected:
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
private:
	int mSize;
	std::string mName;
};

