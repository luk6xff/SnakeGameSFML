#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState
{
public:	
	explicit BaseState(StateManager * const stateManager)
	{
		mStateManager = stateManager;
	}

	virtual ~BaseState() {}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& time) = 0;
	virtual void draw() = 0;

	StateManager* getStateManager()
	{
		return mStateManager;
	}
protected:
	StateManager * mStateManager;

};