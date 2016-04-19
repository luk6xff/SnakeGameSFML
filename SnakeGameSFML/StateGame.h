#pragma once
#include "BaseState.h"
#include "World.h"
#include "EventManager.h"
class StateGame :
	public BaseState
{
public:
	explicit StateGame(StateManager*const stateManager,sf::Vector2u windSize, int blockSize);
	~StateGame();

	void onCreate() override;
	void onDestroy() override;

	void activate() override;
	void deactivate() override;

	void update(const sf::Time& time)override;
	void draw() override;

	void GoToMainMenu(EventDetails* evDetails);
	void GoToPause(EventDetails* evDetails);

private:
	World mWorld;
};

