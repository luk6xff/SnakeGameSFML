#pragma once
#include <vector>
#include <unordered_map>

#include "BaseState.h"
#include "StateContext.h"

enum class StateType 
{
	InvalidState=-1,
	Intro = 0,
	MainMenu,
	Game,
	Pause,
	GameOver
};

//game state container
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

// State factory
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	explicit StateManager(StateContext* const context);
	~StateManager();

	void update(const sf::Time& time);
	void draw();

	StateContext* getStateContext();
	bool hasState(const StateType& stateType);

	void switchTo(const StateType& stateType);
	void remove(const StateType& stateType);

private:
	// Methods.
	void createState(const StateType& stateType);
	void removeState(const StateType& stateType);

	template<class T>
	void RegisterState(const StateType& stateType) {
		m_stateFactory[stateType] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}

	// Members.
	StateContext* mContext;
	StateContainer mStates;
	StateFactory mStateFactory;

};

