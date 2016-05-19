#include "Game.h"
#include "Configuration.h"
Game::Game() : mWindow("Snake", sf::Vector2u(800, 600)),mStateContext(&mWindow,mWindow.getEventManager()),mStateManager(&mStateContext)
{
	Configuration::initialize();
	mClock.restart();
	srand(time(nullptr));
	mStateManager.switchTo(StateType::Intro);
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
	mElapsedTime = mClock.restart(); 
}

Window* Game::getWindow()
{ 
	return &mWindow; 
}


void Game::update()
{
	mWindow.update();
	mStateManager.update(mElapsedTime);
}

void Game::render()
{
	mWindow.beginDraw();
	mStateManager.draw();
	mWindow.endDraw();
	restartClock();
}