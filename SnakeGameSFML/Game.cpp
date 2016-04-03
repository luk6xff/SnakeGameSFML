#include "Game.h"

Game::Game() : mWindow("Snake", sf::Vector2u(800, 600)),
	mSnake(mWorld.getBlockSize()),
	mWorld(sf::Vector2u(800, 600))
{
	mClock.restart();
	srand(time(nullptr));

	mElapsed = 0.0f;

}

Game::~Game(){}

sf::Time Game::getElapsed(){ return mClock.getElapsedTime(); }
void Game::restartClock(){ mElapsed += mClock.restart().asSeconds(); }
Window* Game::getWindow(){ return &mWindow; }

void Game::handleInput(){
	// Input handling.
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
		&& mSnake.getPhysicalDirection() != Direction::Down){
		mSnake.setDirection(Direction::Up);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
		&& mSnake.getPhysicalDirection() != Direction::Up){
		mSnake.setDirection(Direction::Down);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		&& mSnake.getPhysicalDirection() != Direction::Right){
		mSnake.setDirection(Direction::Left);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		&& mSnake.getPhysicalDirection() != Direction::Left){
		mSnake.setDirection(Direction::Right);
	}
}

void Game::update(){
	mWindow.update();
	float timestep = 1.0f / mSnake.getSpeed();
	if(mElapsed >= timestep){
		mSnake.tick();
		mWorld.update(mSnake);
		mElapsed -= timestep;
		if (mSnake.hasLost()){
			mSnake.reset();
		}
	}
}

void Game::render(){
	mWindow.beginDraw();
	// Render here.
	mWorld.render(*mWindow.getRenderWindow());
	mSnake.render(*mWindow.getRenderWindow());

	mWindow.endDraw();
}