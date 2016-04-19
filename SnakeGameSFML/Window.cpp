#include "Window.h"

Window::Window()
{ 
	setup("SnakeGame_igbt6_2016", sf::Vector2u(640, 480)); 
}

Window::Window(const std::string& title, const sf::Vector2u& size)
{ 
	setup(title, size); 
}

Window::~Window()
{ 
	destroy(); 
}

EventManager * Window::getEventManager()
{
	return &mEventManager;
}

void Window::setup(const std::string title, const sf::Vector2u& size){
	mWindowTitle = title;
	mWindowSize = size;
	mIsFullscreen = false;
	mIsDone = false;
	mIsFocused = true;

	mEventManager.addCallback(StateType(-1),"FullscreenToggle",&Window::toggleFullScreen, this);
	mEventManager.addCallback(StateType(-1),"WindowClose",&Window::close, this);
	create();
}

void Window::create()
{
	auto style = (mIsFullscreen ? sf::Style::Fullscreen
		: sf::Style::Default);
	mWindow.create({ mWindowSize.x, mWindowSize.y, 32 },
		mWindowTitle, style);
}

void Window::destroy()
{
	mWindow.close();
}

void Window::beginDraw()
{ 
	mWindow.clear(sf::Color::Black);
}

void Window::endDraw()
{
	mWindow.display(); 
}

bool Window::isDone()
{ 
	return mIsDone; 
}

bool Window::isFullscreen()
{ 
	return mIsFullscreen; 
}

sf::RenderWindow* Window::getRenderWindow()
{ 
	return &mWindow; 
}

sf::Vector2u Window::getWindowSize()
{ 
	return mWindowSize; 
}

//callbacks
void Window::toggleFullScreen(EventDetails* evDetails)
{
	mIsFullscreen = !mIsFullscreen;
	mWindow.close();
	create();
}

void Window::close (EventDetails* evDetails) 
{
	mIsDone = true;
}


void Window::update()
{
	sf::Event event;
	while(mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus) 
		{
			mIsFocused = false;
			mEventManager.setFocus(false); 
		}
		else if (event.type == sf::Event::GainedFocus) 
		{ 
			mIsFocused = true; 
			mEventManager.setFocus(true); 
		}
		
		mEventManager.handleEvent(event);
	}

	mEventManager.update();
}