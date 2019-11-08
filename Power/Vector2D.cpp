#include "Power.h"
#include "Vector2D.h"

Vector2D::Vector2D()
{
	X = 0;
	Y = 0;
}

Vector2D::Vector2D(double x, double y)
{
	X = x;
	Y = y;
}

Vector2D::Vector2D(const Vector2D& other)
{
	X = other.X;
	Y = other.Y;
}

Vector2D::~Vector2D(){}

Vector2D& Vector2D::add(const Vector2D& other)
{
	Vector2D V(0,0);
	V.X = this->X + other.X;
	V.Y = this->Y + other.Y;
	return V;
}

Vector2D& Vector2D::subtract(const Vector2D& other)
{
	Vector2D V(0, 0);
	V.X = this->X - other.X;
	V.Y = this->Y - other.Y;
	return V;
}

Vector2D& Vector2D::multiply(const double scalar)
{
	Vector2D V(0, 0);
	V.X = this->X * scalar;
	V.Y = this->Y * scalar;
	return V;
}

Vector2D& Vector2D::divide(const double scalar)
{
	Vector2D V(0, 0);
	V.X = this->X / scalar;
	V.Y = this->Y / scalar;
	return V;
}

double Vector2D::dot(const Vector2D& other)
{
	return this->X*other.X + this->Y*other.Y;
}

Vector2D& operator+ (Vector2D& left, const Vector2D& right)
{
	return left.add(right);
}

Vector2D& operator- (Vector2D& left, const Vector2D& right)
{
	return left.subtract(right);
}

Vector2D& operator* (Vector2D& left, const double& scalar)
{
	return left.multiply(scalar);
}

Vector2D& operator/ (Vector2D& left, const double& scalar)
{
	return left.divide(scalar);
}
Vector2D& Vector2D::operator= (const Vector2D& other)
{
	this->X = other.X;
	this->Y = other.Y;
	return *this;
}

Vector2D& Vector2D::operator+= (const Vector2D& other)
{
	this->X += other.X;
	this->Y += other.Y;
	return *this;
}

Vector2D& Vector2D::operator-= (const Vector2D& other)
{
	this->X -= other.X;
	this->Y -= other.Y;
	return *this;
}

Vector2D& Vector2D::operator*= (const double scalar)
{
	this->X *= scalar;
	this->Y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/= (const double scalar)
{
	this->X /= scalar;
	this->Y /= scalar;
	return *this;
}

bool Vector2D::operator== (const Vector2D& other)
{
	return (X == other.X && Y == other.Y);
}

bool  Vector2D::operator!= (const Vector2D& other)
{
	return !(X == other.X && Y == other.Y);
}

double Vector2D::Magnitude() const
{
	return sqrt(X*X + Y*Y);
}

double Vector2D::MagnitudeSquared() const
{
	return X*X + Y * Y;
}

void Vector2D::clampMagnitude(double val)
{
	if(MagnitudeSquared() > val)
	{
		setMagnitude(val);
	}
}

void Vector2D::setMagnitude(double mag)
{
	double curMag = Magnitude();
	X *= curMag / mag;
	Y *= curMag / mag;
}

void Vector2D::normalize()
{
	double mag = sqrt(X*X + Y * Y);
	double invMag = 1 / mag;
	*this *= invMag;
}

void Vector2D::Set(double x, double y)
{
	X = x;
	Y = y;
}

void Vector2D::Set(const Vector2D& other)
{
	X = other.X;
	Y = other.Y;
}

string Vector2D::toString() const
{
	std::stringstream ss;
	ss << "(" << X << ", " << Y << ")";
	return ss.str();
}

ostream& operator<<(ostream& out, const Vector2D& vec) // output
{
	out << vec.toString();
	return out;
}

Vector2D Vector2D::UP()
{
	Vector2D vec(0,-1);
	return vec;
}

Vector2D Vector2D::DOWN()
{
	Vector2D vec(0, 1);
	return vec;
}

Vector2D Vector2D::LEFT()
{
	Vector2D vec(-1, 0);
	return vec;
}

Vector2D Vector2D::RIGHT()
{
	Vector2D vec(1, 0);
	return vec;
}
