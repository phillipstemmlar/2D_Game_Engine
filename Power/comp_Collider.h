#pragma once

#ifndef COMP_COLLIDER_H
#define COMP_COLLIDER_H

#include "Power.h"

class Collision;
class CollisionHandler;

class comp_Collider : public Component
{
private:
	SDL_Rect* box;
	SDL_Color color;
	SDL_Color defaultColor;

	CollisionHandler* handler;

	double scale;
	
	bool enabled;
	bool drawing;

	bool future;

	static int count;
	int id;
public:
	comp_Collider();
	~comp_Collider();

	void Update(double deltaTime);
	void Init();
	void Draw();

	void handleCollision(Collision* col);

	bool hasHandler();
	void setHandler(CollisionHandler* handle);

	void Enable();
	void Disable();

	void useFutureCollision();
	void noFutureCollision();
	bool getFutureCollision();

	void setDrawing(bool D);
	void setDrawColor(int r, int g, int b, int a = 255);
	void setDefaultDrawColor(int r, int g, int b, int a = 255);

	SDL_Rect getBox() const;

	int getID() const;
};

#endif