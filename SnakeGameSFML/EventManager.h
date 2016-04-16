#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo
{

	EventInfo()
	{
		mEventCode = 0;
	}
	
	EventInfo(int eventCode) 
	{
		mEventCode = eventCode;
	}

	int mEventCode;
};


struct EventDetails {
	EventDetails(const std::string& bindName)
		: mName(bindName) {
		clear();
	}
	std::string mName;

	sf::Vector2i mSize;
	sf::Uint32 mTextEntered;
	sf::Vector2i mMouse;
	int mMouseWheelDelta;
	int mKeyCode; // Single key code.

	void clear() {
		mSize = sf::Vector2i(0, 0);
		mTextEntered = 0;
		mMouse = sf::Vector2i(0, 0);
		mMouseWheelDelta = 0;
		mKeyCode = -1;
	}
};


using Events = std::vector<std::pair<EventType, EventInfo>>;
struct Binding
{
	Binding(const std::string& name) : mName(name), mEventDetails(name) {}
	void bindEvent(EventType type, EventInfo info = EventInfo()) {
		mEvents.emplace_back(type, info);
	}
	Events mEvents;
	std::string mName;
	EventDetails mEventDetails;

};



using Bindings = std::unordered_map<std::string, Binding*>;
using Callbacks = std::unordered_map<std::string, std::function<void()>>;

class EventManager
{
public:
	EventManager();
	~EventManager();


	bool addBinding(Binding *binding);
	bool removeBinding(const std::string& name);

	inline void setFocus(const bool& focus)
	{
		mHasFocus = focus;
	}
	
	template<class T>
	bool addCallback(const std::string& name, void(T::*func)(), T* instance) 
	{
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return mCallbacks.emplace(name, temp).second;
	}

	void removeCallback(const std::string& name) 
	{
		mCallbacks.erase(name);	
	}

	void handleEvent(sf::Event& event);
	void update();

	inline sf::Vector2i getMousePosition(sf::RenderWindow* window = nullptr)
	{
		return window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition();
	}


private:
	void loadBindings();

	Callbacks mCallbacks;
	Bindings mBindings;
	bool mHasFocus;
};

