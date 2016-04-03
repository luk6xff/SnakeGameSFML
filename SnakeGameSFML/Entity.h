#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
class Entity: public sf::Transformable, public sf::Drawable
{

public:
	Entity();
	virtual ~Entity();
	sf::Vector2f getWorldPosition()const;

protected:
	virtual void update()=0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const=0;
};

