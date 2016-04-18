#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isDone();
	bool isFullscreen();
	bool isFocused();
	sf::RenderWindow* getRenderWindow();
	sf::Vector2u getWindowSize();

	void toggleFullScreen(EventDetails* evDetails=nullptr);
	void close(EventDetails* evDetails = nullptr);

	void draw(sf::Drawable& drawable);

	EventManager* getEventManager();
private:
	void setup(const std::string title, const sf::Vector2u& size);
	void create();
	void destroy();

	EventManager mEventManager;
	sf::RenderWindow mWindow;
	sf::Vector2u mWindowSize;
	std::string mWindowTitle;
	bool mIsDone;
	bool mIsFullscreen;
	bool mIsFocused;
};