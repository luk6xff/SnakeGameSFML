#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

sf::Vector2f Entity::getWorldPosition() const
{
	sf::Transform transform = sf::Transform::Identity;
	transform=getTransform() * transform;
	return transform*sf::Vector2f();
}
