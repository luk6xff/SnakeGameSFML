#include "Entity.h"


Entity::Entity(const sf::Texture & texture):mTexture(texture),mSprite(mTexture)
{

}

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

void Entity::setTexture(const sf::Texture & texture)
{

		mTexture = texture;
}

sf::Texture & Entity::getTexture()
{
	return mTexture;
}

void Entity::setSprite(const sf::Sprite & sprite)
{
	mSprite = sprite;
}

sf::Sprite & Entity::getSprite()
{
	return mSprite;
}
