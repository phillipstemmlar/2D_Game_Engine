#include "Line2D.h"

Line2D::Line2D() : Drawable()
{
	A.Set(0,0);
	A.Set(0,0);
}

Line2D::Line2D(Vector2D a, Vector2D b) : Drawable()
{
	A.Set(a);
	A.Set(b);
}

Line2D::Line2D(double x1, double y1, double x2, double y2) : Drawable()
{
	A.Set(x1,y1);
	A.Set(x2,y2);
}

Line2D::~Line2D()
{
}

Vector2D Line2D::point(double t) const
{
	Vector2D a(A);	a *= t;
	Vector2D b(B);	b *= (1-t);

	Vector2D x(a.X+b.X, a.Y+b.Y);
	return x;
}

bool Line2D::intersects(Vector2D point) const
{
	if ((A.X - B.X) == 0) { return (point.X == A.X); }

	double tx = (point.X - B.X) / (A.X - B.X);
	double ty = (point.Y - B.Y) / (A.Y - B.Y);

	return (tx == ty) && (tx >= 0) && (tx <= 1);
}

bool Line2D::intersects(const Line2D& line, Vector2D* intersectPoint) const
{
	if ((A.X - B.X) == 0) {



		return false;
	} else {
		double ax_bx = A.X - B.X;
		double ay_by = A.Y - B.Y;
		
		double top = (line.B.X - B.X)*(ay_by/ax_bx) + B.Y - line.B.Y;
		double bottom = line.A.Y - line.B.Y - (line.A.X - line.B.X)*(ay_by / ax_bx);

		if (bottom == 0) { return false; }

		double r = top / bottom;

		//double r = (line.B.Y - B.Y - line.B.X + B.X) / (line.A.X - line.B.X - line.A.Y + line.B.Y);
		//double t = (B.Y - line.B.Y - B.X + line.B.X) / (A.X - B.X - A.Y + B.Y);

		if (intersectPoint != null) {
			intersectPoint->Set(line.point(r));
		}
		return (r >= 0) && (r <= 1);// && (t >= 0) && (t <= 1);
	}
}

bool Line2D::intersects(SDL_Rect rect) const
{
	Vector2D a(rect.x, rect.y);
	Vector2D b(rect.x + rect.w, rect.y);
	Vector2D c(rect.x, rect.y + rect.h);
	Vector2D d(rect.x + rect.w, rect.y + rect.h);

	Line2D AB(a, b);
	Line2D AC(a, c);
	Line2D BD(b, d);
	Line2D CD(c, d);

	bool LxAB = intersects(AB, null);
	bool LxAC = intersects(AB, null);
	bool LxBD = intersects(AB, null);
	bool LxCD = intersects(AB, null);

	return LxAB || LxAC || LxBD || LxCD;
}

void Line2D::Draw(SDL_Renderer* rend)
{
	SDL_RenderDrawLine(rend,A.X,A.Y,B.X,B.Y);
}

string Line2D::toString() const
{
	stringstream ss;
	ss << "Line: A(" << A.X << "," << A.Y << ")  B(" << B.X << "," << B.Y << ")";
	return ss.str();
}