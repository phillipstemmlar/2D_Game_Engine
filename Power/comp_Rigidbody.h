#pragma once

#ifndef COMP_RIGIDBODY_H
#define COMP_RIGIDBODY_H

#include "Power.h"

class comp_Rigidbody : public Component
{
private:
	Vector2D gravity;
	double gravityConst;
	
	double maxSpeed;
	double maxRotationSpeed;
public:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	Vector2D force;

	double angularPosition;
	double angularVelocity;
	double angularAcceleration;
	double torque;

	double mass;
	double rotInertia();

	comp_Rigidbody();
	~comp_Rigidbody();

	void Update(double deltaTime);

	void applyForce(Vector2D F);
	void applyTorque(double T);

	Vector2D getGravity();

	double getGravityConst() const;
	void setGravityConst(double a);

	void setMaxSpeed(double speed);
	double getMaxSpeed();

	void setMaxRotSpeed(double rotSpeed);
	double getMaxRotSpeed();

	void print();
};

#endif