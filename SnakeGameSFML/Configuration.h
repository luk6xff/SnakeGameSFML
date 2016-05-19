#pragma once
#include <SFML/Graphics.hpp> //Texture
#include "ResourceManager.h" //ResourceManager


class Configuration
{
public:
	Configuration()=delete;
	Configuration(const Configuration&) = delete;
	Configuration& operator = (const Configuration&) = delete;

	static ResourceManager<sf::Texture, int> textures;
	enum Textures :int 
	{
		SnakeHead,
		SnakeBody,
		Fruit,
		StateIntroTexture
	};


	static void initialize();

private:
	static void initTextures();

};

