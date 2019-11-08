#include "Power.h"
#include "Event.h"


Event::Event()
{
}


Event::~Event()
{
}

void Event::handle(double deltaTime)
{
	onHandle(deltaTime);
}

void Event::onHandle(double deltaTime)
{
	Log("Handling event");
}
