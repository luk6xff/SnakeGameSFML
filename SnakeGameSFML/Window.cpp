#include "Window.h"

Window::Window(){ setup("Window", sf::Vector2u(640, 480)); }
Window::Window(const std::string& title, const sf::Vector2u& size){ setup(title, size); }
Window::~Window(){ destroy(); }

void Window::setup(const std::string title, const sf::Vector2u& size){
	mWindowTitle = title;
	mWindowSize = size;
	mIsFullscreen = false;
	mIsDone = false;
	create();
}

void Window::create(){
	auto style = (mIsFullscreen ? sf::Style::Fullscreen
		: sf::Style::Default);
	mWindow.create({ mWindowSize.x, mWindowSize.y, 32 },
		mWindowTitle, style);
}

void Window::destroy(){
	mWindow.close();
}

void Window::beginDraw(){ mWindow.clear(sf::Color::Black); }
void Window::endDraw(){ mWindow.display(); }

bool Window::isDone(){ return mIsDone; }
bool Window::isFullscreen(){ return mIsFullscreen; }

sf::RenderWindow* Window::getRenderWindow(){ return &mWindow; }
sf::Vector2u Window::getWindowSize(){ return mWindowSize; }

void Window::toggleFullscreen(){
	mIsFullscreen = !mIsFullscreen;
	mWindow.close();
	create();
}

void Window::update(){
	sf::Event event;
	while(mWindow.pollEvent(event)){
		if(event.type == sf::Event::Closed){ mIsDone = true; }
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){ mIsDone = true; }
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5){ toggleFullscreen(); }
	}
}