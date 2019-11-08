#pragma once
class Event
{
private:


public:
	Event();
	~Event();

	void handle(double deltaTime);
	virtual void onHandle(double deltaTime);

};

