#pragma once

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "Power.h"

class Event;

class EventManager
{
private:
	Queue<Event*> Events;

public:
	EventManager();
	~EventManager();

	void Handle(double deltaTime);

	void addEvent(Event* e);

};

#endif