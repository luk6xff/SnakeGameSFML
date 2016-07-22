#include "StateIntro.h"
#include "Configuration.h"



StateIntro::StateIntro(StateManager * stateManager):BaseState(stateManager)
{
}

StateIntro::~StateIntro()
{
}

void StateIntro::onCreate()
{
	mTimePassed = 0.0f;

	sf::Vector2u windowSize = getStateManager()->getStateContext()->mWindow->getRenderWindow()->getSize();
	
	mIntroSprite.setTexture(Configuration::textures.get(Configuration::Textures::StateIntroTexture));
	mIntroSprite.setOrigin(Configuration::textures.get(Configuration::Textures::StateIntroTexture).getSize().x / 2.0f, Configuration::textures.get(Configuration::Textures::StateIntroTexture).getSize().y / 2.0f);
	mIntroSprite.setPosition(windowSize.x / 2.0f, 0);

	mIntroFont.loadFromFile("media/arial.ttf");
	mIntroText.setFont(mIntroFont);
	mIntroText.setString({ "Press SPACE to continue" });
	mIntroText.setCharacterSize(20);
	sf::FloatRect textRect = mIntroText.getLocalBounds();
	mIntroText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	mIntroText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	
	EventManager *eventMgr = mStateManager->getStateContext()->mEventManager;
	eventMgr->addCallback(StateType::Intro, "IntroGoToGame", &StateIntro::goToGame, this);

}

void StateIntro::onDestroy()
{
	EventManager *eventMgr = mStateManager->getStateContext()->mEventManager;
	eventMgr->removeCallback(StateType::Intro, "IntroGoToGame");
}

void StateIntro::activate()
{
	//stub
}

void StateIntro::deactivate()
{
	//stub
}

void StateIntro::update(const sf::Time & time)
{
	
	if( mTimePassed<5.0f  )
	{ 
		mTimePassed += time.asSeconds();
		sf::Vector2u windowSize = getStateManager()->getStateContext()->mWindow->getRenderWindow()->getSize();
		if(mIntroSprite.getPosition().y <= (windowSize.y))
			mIntroSprite.setPosition(mIntroSprite.getPosition().x,mIntroSprite.getPosition().y + (100 * time.asSeconds()));
	}
}
 
void StateIntro::draw()
{
	sf::RenderWindow* window = mStateManager->getStateContext()->mWindow->getRenderWindow();
	window->draw(mIntroSprite);
	if (mTimePassed >= 5.0f) {
		window->draw(mIntroText);
	}

}

void StateIntro::goToGame(EventDetails * evDetails)
{
	if (mTimePassed >= 5.0f)
	{
		mStateManager->switchTo(StateType::Game);
		mStateManager->remove(StateType::Intro);

	}
}
