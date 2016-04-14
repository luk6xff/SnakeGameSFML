#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"

class Game{
public:
	Game();
	~Game();

	void handleInput();
	void update();
	void render();

	sf::Time getElapsed();
	void restartClock();

	Window* getWindow();
private:
	Window mWindow;
	sf::Clock mClock;
	float mElapsed;

	World mWorld;
};