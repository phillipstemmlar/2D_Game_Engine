#pragma once

#ifndef COLLISION_H
#define COLLISION_H

#include "Power.h"

class comp_Rigidbody;
class comp_Collider;

class Collision
{
public:
	comp_Rigidbody * RigidBody;
	comp_Collider * other;

	Collision(comp_Rigidbody* rigid,comp_Collider* coldr);
	~Collision();
};


#endif // !COLLISION_H