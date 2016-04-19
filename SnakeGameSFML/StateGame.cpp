#include "StateGame.h"
#include "StateManager.h"



StateGame::StateGame(StateManager* stateManager, sf::Vector2u windSize, int blockSize):BaseState(stateManager),mWorld(windSize, blockSize)
{
	EventManager* evManager = getStateManager()->getStateContext()->mEventManager;
	mWorld.setupEventHandling(StateType::Game, evManager);
	evManager->addCallback(StateType::Game, "KeyEscape", &StateGame::GoToMainMenu, this);
	evManager->addCallback(StateType::Game, "KeyP", &StateGame::GoToPause, this);

}


StateGame::~StateGame()
{
	EventManager* evManager = getStateManager()->getStateContext()->mEventManager;
	evManager->removeCallback(StateType::Game, "KeyEscape");
	evManager->removeCallback(StateType::Game, "KeyP");
}

void StateGame::onCreate()
{
}

void StateGame::onDestroy()
{
}

void StateGame::activate()
{
}

void StateGame::deactivate()
{
}

void StateGame::update(const sf::Time & time)
{
	mWorld.update();	
}

void StateGame::draw()
{
	
	mWorld.render(*(getStateManager()->getStateContext()->mWindow->getRenderWindow()));
}

void StateGame::GoToMainMenu(EventDetails * evDetails)
{
	getStateManager()->switchTo(StateType::MainMenu);
}

void StateGame::GoToPause(EventDetails * evDetails)
{
	getStateManager()->switchTo(StateType::Pause);
}
