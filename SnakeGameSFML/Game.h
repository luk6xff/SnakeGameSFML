#pragma once
#include "Window.h"
#include "World.h"
#include "StateContext.h"
#include "StateManager.h"

class Game{
public:
	Game(); //ctr
	//non copyable class
	Game(const Game&) = delete; //copy ctr
	Game(const Game&&) = delete; //move ctr
	Game & operator= (const Game&) = delete; //assignment optr
	~Game();

	void runWithFixedTimeSteps(int nrOfFramesPerSecond = 60);
	void runWithVariableTimeSteps();
	void runWithMinimumTimeSteps(int minNrOfFramesPerSecond = 30);

private:
	Window mWindow;
	StateContext mStateContext;
	StateManager mStateManager;
	
	void processEvents();// processes all the events
	void update(sf::Time deltaTime);
	void render(); //draw all

	
};