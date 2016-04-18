#pragma once
#include "Window.h"
#include "EventManager.h"
struct StateContext {
	StateContext()
		:mWindow(nullptr),
		mEventManager(nullptr) {}
	Window* mWindow;
	EventManager* mEventManager;
};