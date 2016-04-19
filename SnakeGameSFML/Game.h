#pragma once
#include "Window.h"
#include "World.h"
#include "StateContext.h"
#include "StateManager.h"

class Game{
public:
	Game();
	~Game();

	void update();
	void render();

	sf::Time getElapsed();
	void restartClock();
	Window* getWindow();
private:
	Window mWindow;
	StateContext mStateContext;
	StateManager mStateManager;

	sf::Clock mClock;
	sf::Time mElapsedTime;

	
};