#pragma once

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Power.h"

class comp_Collider;
class comp_Rigidbody;
class Collision;
class Line2D;

class CollisionManager
{
private:
	std::vector<comp_Collider*> Colliders;
	std::vector<comp_Rigidbody*> RigidBodies;

	Queue<Collision*> Collisions;

public:
	CollisionManager();
	~CollisionManager();

	void Update(double deltaTime);
	void Draw();

	void checkCollisions(); 
	void handleCollisions();

	void addCollider(comp_Collider* obj);
	void addRigidbody(comp_Rigidbody* obj);
	//remove by calling go.Destroy();

	void setAllColliderDrawColor(int r, int g, int b, int a = 255);

	static bool AABB(comp_Rigidbody* rigid, comp_Collider* col);
	static bool AABB(comp_Collider* col1, comp_Collider* col2);

	static bool AABB_future(comp_Rigidbody* rigid, comp_Collider* col);

	static bool lineCollision(Line2D line, Queue<comp_Collider*> cols);
	static bool lineCollision(const Line2D & line, Queue<comp_Collider*> cols, string filterTag);

	void newCollision(comp_Rigidbody* rigid, comp_Collider* col);
};

#endif