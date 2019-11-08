#pragma once

#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "Power.h"

class comp_Collider;

class CollisionHandler
{
protected:
	comp_Collider* collider;
public:
	CollisionHandler(comp_Collider* col) { collider = col; };
	~CollisionHandler() {};

	virtual void onCollision(Collision* col) {}
};

#endif