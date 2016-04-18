#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"

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
	World mWorld;
	sf::Clock mClock;
	float mElapsed;

	
};