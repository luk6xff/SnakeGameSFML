#include "Game.h"

Game::Game() : mWindow("Snake", sf::Vector2u(800, 600)),mStateContext(&mWindow,mWindow.getEventManager()),mStateManager(&mStateContext)
{
	mClock.restart();
	srand(time(nullptr));
	mStateManager.switchTo(StateType::Game);
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