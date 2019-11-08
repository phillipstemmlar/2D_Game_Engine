#pragma once

#ifndef LINE2D_H
#define LINE2D_H

#include "Power.h"

class Line2D : public Drawable
{
protected:
	void Draw(SDL_Renderer* rend);

public:
	Line2D();
	Line2D(Vector2D a, Vector2D b);
	Line2D(double x1, double y1, double x2, double y2);
	~Line2D();

	Vector2D point(double t) const;

	bool intersects(Vector2D point) const;
	bool intersects(const Line2D& line, Vector2D* intersectPoint) const;
	bool intersects(SDL_Rect rect) const;

	string toString() const;

	Vector2D A, B;
};

#endif