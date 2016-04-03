#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
	sf::RenderWindow* getRenderWindow();
	sf::Vector2u getWindowSize();

	void toggleFullscreen();

	void draw(sf::Drawable& drawable);
private:
	void setup(const std::string title, const sf::Vector2u& size);
	void create();
	void destroy();

	sf::RenderWindow mWindow;
	sf::Vector2u mWindowSize;
	std::string mWindowTitle;
	bool mIsDone;
	bool mIsFullscreen;
};