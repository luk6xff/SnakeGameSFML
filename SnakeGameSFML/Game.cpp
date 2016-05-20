#include "Game.h"
#include "Configuration.h"
Game::Game() : mWindow("Snake", sf::Vector2u(800, 600)),mStateContext(&mWindow,mWindow.getEventManager()),mStateManager(&mStateContext)
{
	Configuration::initialize();
	mStateManager.switchTo(StateType::Intro);
}

Game::~Game()
{
}

void Game::runWithFixedTimeSteps(int nrOfFramesPerSecond)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / nrOfFramesPerSecond);

	while (!mWindow.isDone())
	{
		processEvents();
		bool repaint = false;
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			repaint = true;
			update(timePerFrame);
		}
		if (repaint)
			render();
	}

}

void Game::runWithVariableTimeSteps()
{
	sf::Clock clock;
	while (!mWindow.isDone())
	{
		processEvents();
		update(clock.restart());
		render();
	}
}

void Game::runWithMinimumTimeSteps(int minNrOfFramesPerSecond)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / minNrOfFramesPerSecond);

	while (!mWindow.isDone())
	{
		processEvents();
		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		update(timeSinceLastUpdate);
		render();
	}
}


void Game::update(sf::Time deltaTime)
{
	mWindow.update();
	mStateManager.update(deltaTime);
}

void Game::processEvents()
{
}

void Game::render()
{
	mWindow.beginDraw();
	mStateManager.draw();
	mWindow.endDraw();
}