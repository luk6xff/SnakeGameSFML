#include "Configuration.h"




ResourceManager<sf::Texture, int> Configuration::textures;


void Configuration::initialize() 
{
	initTextures();
}


void Configuration::initTextures()
{
	//textures.load(Textures::SnakeHead, "media/snakeTexture.jpg", sf::IntRect(0, 0, 16, 16));
	textures.load(Textures::StateIntroTexture, "media/introTexture.png"/*, sf::IntRect(0, 0, 16, 16)*/);
}


