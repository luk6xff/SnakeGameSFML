#pragma once
#include "BaseState.h"
#include "EventManager.h"
class StateMainMenu :
	public BaseState
{
public:
	StateMainMenu(StateManager* stateManager);
	~StateMainMenu();


	void onCreate() override;
	void onDestroy() override;

	void activate() override;
	void deactivate() override;

	void update(const sf::Time& time)override;
	void draw() override;

	void goToPlay(EventDetails* evDetails);
	void goToExit(EventDetails* evDetails);
};

