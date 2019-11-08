#pragma once

#ifndef COMP_TRANSFORM_H
#define COMP_TRANSFORM_H

#include "Power.h"

class comp_Transform : public Component
{
private:
	Vector2D* centerOfRotation;
public:
	comp_Transform( double scale = 1);
	comp_Transform( Vector2D& start, double scale = 1);
	comp_Transform( double X, double Y, double scale = 1);
	~comp_Transform();

	Vector2D* position;

	double rotation;		//radians
	double scale;

	double width = 100;
	double height = 100;

	double rotationDegrees();

	void setCenterOfRotation(int x, int y);
	SDL_Point* getCenterOfRotation_SDL() const;
	Vector2D* getCenterOfRotation() const;

	SDL_Point* getCenterOfMass_SDL() const;
	Vector2D* getCenterOfMass() const;

	void setPosition(double X, double Y);
	void rotateBy(double radians);			//counter-clockwise => positive
	void rotateByDegrees(double degrees);	//		clockwise	=> negative

	static double RadToDeg(double rad);
	static double DegToRad(double deg);

	void Init(){}
};

#endif