#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class Entity: public sf::Transformable, public sf::Drawable
{

public:
	explicit Entity(const sf::Texture& texture);
	Entity();
	virtual ~Entity();
	sf::Vector2f getWorldPosition()const;

	void setTexture(const sf::Texture& texture);

	sf::Texture& getTexture();

	void setSprite(const sf::Sprite& sprite);

	sf::Sprite& getSprite();

protected:
	virtual void update()=0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const=0;
	sf::Texture mTexture;
	sf::Sprite mSprite;
};

