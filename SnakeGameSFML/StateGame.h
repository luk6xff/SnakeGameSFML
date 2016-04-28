#pragma once
#include "BaseState.h"
#include "World.h"
#include "EventManager.h"
class StateGame :
	public BaseState
{
public:
	explicit StateGame(StateManager* stateManager,sf::Vector2u windSize, int blockSize);
	StateGame(StateManager* stateManager);
	~StateGame();

	void onCreate() override;
	void onDestroy() override;

	void activate() override;
	void deactivate() override;

	void update(const sf::Time& time)override;
	void draw() override;

	void goToMainMenu(EventDetails* evDetails);
	void goToPause(EventDetails* evDetails);

private:
	World mWorld;
};

