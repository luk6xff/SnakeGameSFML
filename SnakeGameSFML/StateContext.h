#pragma once
#include "Window.h"
#include "EventManager.h"
struct StateContext {
	
	explicit StateContext(Window* const mWindow, EventManager* const mEventManager)
		:mWindow(mWindow),
		mEventManager(mEventManager) {}
	
	Window* mWindow;
	EventManager* mEventManager;
};