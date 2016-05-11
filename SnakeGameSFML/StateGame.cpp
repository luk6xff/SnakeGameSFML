#include "StateGame.h"
#include "StateManager.h"



StateGame::StateGame(StateManager* stateManager, sf::Vector2u windSize, int blockSize):BaseState(stateManager),mWorld(windSize, blockSize)
{
	EventManager* evManager = getStateManager()->getStateContext()->mEventManager;
	mWorld.setupEventHandling(StateType::Game, evManager);
	evManager->addCallback(StateType::Game, "KeyEscape", &StateGame::goToMainMenu, this);
	evManager->addCallback(StateType::Game, "KeyP", &StateGame::goToPause, this);

}

StateGame::StateGame(StateManager * stateManager) :BaseState(stateManager), mWorld(sf::Vector2u(800,600), 16)
{
	EventManager* evManager = getStateManager()->getStateContext()->mEventManager;
	mWorld.setupEventHandling(StateType::Game, evManager);
	evManager->addCallback(StateType::Game, "KeyEscape", &StateGame::goToMainMenu, this);
	evManager->addCallback(StateType::Game, "KeyP", &StateGame::goToPause, this);
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

void StateGame::goToMainMenu(EventDetails * evDetails)
{
	getStateManager()->switchTo(StateType::MainMenu);
}

void StateGame::goToPause(EventDetails * evDetails)
{
	getStateManager()->switchTo(StateType::Pause);
}
