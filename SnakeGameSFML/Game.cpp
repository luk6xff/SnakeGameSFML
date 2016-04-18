#include "Game.h"

Game::Game() : mWindow("Snake", sf::Vector2u(800, 600)),
	mWorld(sf::Vector2u(800, 600),16)
{
	mWorld.setupEventHandling(getWindow()->getEventManager());
	mClock.restart();
	srand(time(nullptr));

	mElapsed = 0.0f;

}

Game::~Game()
{
}

sf::Time Game::getElapsed()
{ 
	return mClock.getElapsedTime(); 
}

void Game::restartClock()
{ 
	mElapsed += mClock.restart().asSeconds(); 
}

Window* Game::getWindow()
{ 
	return &mWindow; 
}


void Game::update()
{
	mWindow.update();
	float timestep = 1.0f / 10;// mSnake.getSpeed();
	if(mElapsed >= timestep){
		mWorld.update();
		mElapsed -= timestep;
	}
}

void Game::render()
{
	mWindow.beginDraw();
	mWorld.render(*mWindow.getRenderWindow());
	mWindow.endDraw();
}