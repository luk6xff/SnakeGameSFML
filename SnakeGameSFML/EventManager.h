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
	KeyPressed = sf::Event::KeyPressed,
	KeyReleased = sf::Event::KeyReleased,
	MButtonPressed = sf::Event::MouseButtonPressed,
	MButtonReleased = sf::Event::MouseButtonReleased,
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
	Binding(const std::string& name) : mName(name), mEventDetails(name), mOccurenceCounter(0){}
	
	void bindEvent(EventType type, EventInfo info = EventInfo()) 
	{
		mEvents.emplace_back(type, info);
	}
	
	void clear()
	{
		mEventDetails.clear();
		mOccurenceCounter = 0;
	}

	Events mEvents;
	std::string mName;
	EventDetails mEventDetails;
	int mOccurenceCounter;



};



using Bindings = std::unordered_map<std::string, Binding*>;
// Callback container.
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
// State callback container.
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
public:
	EventManager();
	~EventManager();
	EventManager(const EventManager& evMng) = delete;
	EventManager operator=(const EventManager& evMng) = delete;

	bool addBinding(Binding *binding);
	bool removeBinding(const std::string& name);

	inline void setCurrentState(StateType state)
	{
		mCurrentState = state;
	}

	inline void setFocus(const bool& focus)
	{
		mHasFocus = focus;
	}
	
	template<class T>
	bool addCallback(StateType stateType, const std::string& name, void(T::*func)(EventDetails*), T* instance) 
	{
		auto itr = mCallbacks.emplace(stateType, CallbackContainer()).first;
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return itr->second.emplace(name, temp).second;
	}

	bool removeCallback(StateType stateType, const std::string& name)
	{
		auto itr = mCallbacks.find(stateType);
		if (itr == mCallbacks.end()) { return false; }
		auto callbackItr = itr->second.find(name);
		if (callbackItr == itr->second.end()) { return false; }
		itr->second.erase(name);
		return true;
	}

	//window polling events
	void handleEvent(sf::Event& event);

	//real time events
	void update();

	inline sf::Vector2i getMousePosition(sf::RenderWindow* window = nullptr)
	{
		return window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition();
	}


private:
	void loadBindings();

	StateType mCurrentState;
	Callbacks mCallbacks;
	Bindings mBindings;
	bool mHasFocus;
};

