#pragma once

#ifndef VECTOR_H
#define VECTOR_H

class Vector2D
{
public:
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(const Vector2D& other);
	~Vector2D();

	Vector2D& add(const Vector2D& other);
	Vector2D& subtract(const Vector2D& other);
	Vector2D& multiply(const double scalar);
	Vector2D& divide(const double scalar);
	double dot(const Vector2D& other);

	friend Vector2D& operator+ (Vector2D& left, const Vector2D& right);
	friend Vector2D& operator- (Vector2D& left, const Vector2D& right);
	friend Vector2D& operator* (Vector2D& left, const double& scalar);
	friend Vector2D& operator/ (Vector2D& left, const double& scalar);

	Vector2D& operator= (const Vector2D& other);
	Vector2D& operator+= (const Vector2D& other);
	Vector2D& operator-= (const Vector2D& other);
	Vector2D& operator*= (const double scalar);
	Vector2D& operator/= (const double scalar);

	bool operator== (const Vector2D& other);
	bool  operator!= (const Vector2D& other);

	double Magnitude() const;
	double MagnitudeSquared() const;

	void clampMagnitude(double val);
	void setMagnitude(double mag);

	void normalize();

	void Set(const Vector2D& other);
	void Set(double x, double y);

	double X;
	double Y;

	string toString() const;
	friend ostream& operator<<(ostream& out, const Vector2D& vec);

	static Vector2D UP();
	static Vector2D DOWN();
	static Vector2D LEFT();
	static Vector2D RIGHT();
};


#endif