#include "EventManager.h"



EventManager::EventManager():mCurrentState(StateType(-1)),mHasFocus(true)
{
	loadBindings();
}


EventManager::~EventManager()
{
	for (auto& binding : mBindings)
	{
		delete binding.second;
		binding.second = nullptr;
	}
}

bool EventManager::addBinding(Binding* binding)
{
	if (binding == nullptr)
		return false;
	if (mBindings.find(binding->mName) != mBindings.end())
		return false;
	
	return mBindings.emplace(binding->mName, binding).second;
}


bool EventManager::removeBinding(const std::string& name)
{
	auto foundBindingItr = mBindings.find(name);
	if(foundBindingItr == mBindings.end())
		return false;
	delete foundBindingItr->second;
	mBindings.erase(foundBindingItr);
	return true;
}


void EventManager::handleEvent(sf::Event& event) 
{
	for (auto& bindingItr : mBindings) 
	{
		Binding * bind = bindingItr.second;
		for (auto& bindingEventItr : bind->mEvents)
		{
			EventType sfmlEvent = (EventType)event.type;
			if (bindingEventItr.first != sfmlEvent)
				continue;
			if (sfmlEvent == EventType::KeyPressed || sfmlEvent == EventType::KeyReleased)
			{
				if (bindingEventItr.second.mEventCode==event.key.code)
				{
					bind->mEventDetails.mKeyCode =bindingEventItr.second.mEventCode; //save code of the current event
					++(bind->mOccurenceCounter);
					
				}
				break; //enough for this event
			}
			else if (sfmlEvent == EventType::MButtonPressed || sfmlEvent == EventType::MButtonReleased)
			{
				if (bindingEventItr.second.mEventCode == event.mouseButton.button)
				{
					bind->mEventDetails.mMouse.x = event.mouseButton.x;
					bind->mEventDetails.mMouse.y = event.mouseButton.y;
					bind->mEventDetails.mKeyCode = bindingEventItr.second.mEventCode; //save code of the current event
					++(bind->mOccurenceCounter);
					break;
				}
			}
			else 
			{
				if (sfmlEvent == EventType::MouseWheel) 
				{
					bind->mEventDetails.mMouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized)
				{
					bind->mEventDetails.mSize.x = event.size.width;
					bind->mEventDetails.mSize.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) 
				{
					bind->mEventDetails.mTextEntered = event.text.unicode;
				}
				++(bind->mOccurenceCounter);
			}
		}
	}
}

void EventManager::update() {
	if (!mHasFocus) 
	{ 
		return; 
	}
	for (auto &bindingItr : mBindings) 
	{
		Binding* bind = bindingItr.second;
		for (auto &bindingEventItr : bind->mEvents) 
		{
			switch (bindingEventItr.first) 
			{
			case(EventType::Keyboard) :
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(bindingEventItr.second.mEventCode))) 
				{
					bind->mEventDetails.mKeyCode = bindingEventItr.second.mEventCode;
					++(bind->mOccurenceCounter);
				}
				break;
			case(EventType::Mouse) :
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(bindingEventItr.second.mEventCode))) 
				{
					bind->mEventDetails.mKeyCode = bindingEventItr.second.mEventCode;
					++(bind->mOccurenceCounter);
				}
				 break;
			case(EventType::Joystick) :
				// for future use
				break;
			}
		}

		if (bind->mOccurenceCounter!=0) 
		{
			{
				std::cout << "CALLBACK " << bind->mName<< std::endl;
				auto stateCallbacks = mCallbacks.find(mCurrentState);
				auto otherCallbacks = mCallbacks.find(StateType(-1));

				if (stateCallbacks != mCallbacks.end()) {
					auto callItr = stateCallbacks->second.find(bind->mName);
					if (callItr != stateCallbacks->second.end()) {
						// Pass in information about events.
						callItr->second(&bind-> mEventDetails);
					}
				}
				if (otherCallbacks != mCallbacks.end()) {
					auto callItr = otherCallbacks->second.find(bind->mName);
					if (callItr != otherCallbacks->second.end()) {
						// Pass in information about events.
						callItr->second(&bind->mEventDetails);
					}
				}
			}
		}
		bind->clear();
	}
}


void EventManager::loadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("keysConfiguration.cfg");
	if (!bindings.is_open()) 
	{ 
		std::cout << "! Failed loading keysConfiguration.cfg" << std::endl; 
		return; 
	}
	std::string line;
	while (std::getline(bindings, line)) 
	{
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) 
		{
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) 
			{ 
				delete bind; 
				bind = nullptr; 
				break; 
			}
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.mEventCode = code;

			bind->bindEvent(type, eventInfo);
		}

		if (!addBinding(bind)) 
		{ 
			delete bind; 
		}
		bind = nullptr;
	}
	bindings.close();


}