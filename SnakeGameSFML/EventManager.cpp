#include "EventManager.h"



EventManager::EventManager():mHasFocus(true)
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
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (bindingEventItr.second.mEventCode)
				{
					
				}
			}
			else if()
		}


	}
}

void EventManager::loadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open()) { std::cout << "! Failed loading keys.cfg." << std::endl; return; }
	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) { delete bind; bind = nullptr; break; }
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.mEventCode = code;

			bind->bindEvent(type, eventInfo);
		}

		if (!addBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();


}