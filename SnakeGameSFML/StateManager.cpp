#include "StateManager.h"
#include "StateMainMenu.h"
#include "StateGame.h"




StateManager::StateManager(StateContext* context):mContext(context)
{
	registerState<StateMainMenu>(StateType::MainMenu);
	registerState<StateGame>(StateType::Game);

}

StateManager::~StateManager()
{
	for (auto& stateItr : mStates)
	{
		stateItr.second->onDestroy();
		delete stateItr.second;
	}
}

void StateManager::update(const sf::Time & time)
{
	if (mStates.empty()) 
	{
		return;
	}
	/*
	if (mStates.back().second->isTranscendent()) 
	{
	
	}
	else*/ 
	{//should be always met
		mStates.back().second->update(time);
	}

}

void StateManager::draw()
{
	if (mStates.empty())
	{
		return;
	}
	mStates.back().second->draw();
}

StateContext * StateManager::getStateContext()
{
	return mContext;
}

bool StateManager::hasState(const StateType & stateType)
{
	return false;
}

void StateManager::switchTo(const StateType & stateType)
{
	mContext->mEventManager->setCurrentState(stateType);
	for (auto itr = mStates.begin();
	itr != mStates.end(); ++itr)
	{
		if (itr->first == stateType) {
			mStates.back().second->deactivate();
			StateType tmpType = itr->first;
			BaseState* tmpState = itr->second;
			mStates.erase(itr);
			mStates.emplace_back(tmpType, tmpState); //put it onto last element
			tmpState->activate();
			return;
		}
	}

	// State with given stateType wasn't found.
	if (!mStates.empty()) 
	{ 
		mStates.back().second->deactivate(); 
		createState(stateType);
		mStates.back().second->activate();
	}
	
}

void StateManager::remove(const StateType & stateType)
{
}

void StateManager::createState(const StateType & stateType)
{	
	auto newState = mStateFactory.find(stateType);
	if (newState == mStateFactory.end())
	{
		return;
	}
	BaseState* state = newState->second();
	mStates.emplace_back(stateType, state);
	state->onCreate();
}

void StateManager::removeState(const StateType & stateType)
{
	for (auto itr = mStates.begin();
	itr != mStates.end(); ++itr)
	{
		if (itr->first == stateType) {
			itr->second->onDestroy();
			delete itr->second;
			mStates.erase(itr);
			return;
		}
	}
}
