#pragma once

#include "BaseState.h"
#include "EventManager.h"
class StateIntro: public BaseState
{
public:
	explicit StateIntro(StateManager* stateManager);
	~StateIntro();
	void onCreate() override;
	void onDestroy() override;

	void activate() override;
	void deactivate() override;

	void update(const sf::Time& time)override;
	void draw() override;
	void goToGame(EventDetails*evDetails);

private:
	sf::Texture mIntroTexture;
	sf::Sprite mIntroSprite;
	sf::Text mIntroText;
	sf::Font mIntroFont;


};


