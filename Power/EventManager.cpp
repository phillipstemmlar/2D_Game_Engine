#include "Power.h"
#include "EventManager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	while (!Events.isEmpty())
	{
		Event* e = Events.pop();	
		if (e){
			delete e;
		}
	}
}

void EventManager::Handle(double deltaTime)
{
	while (!Events.isEmpty())
	{
		Event* e = Events.pop();
		e->handle(deltaTime);
	}
}

void EventManager::addEvent(Event* e)
{
	Events.push(e);
}
