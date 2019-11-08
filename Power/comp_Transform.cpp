#include "Power.h"
#include "comp_Transform.h"


comp_Transform::comp_Transform( double scale) : Component()
{
	this->position = new Vector2D(0,0);
	this->scale = scale;
	this->rotation = 0;
	centerOfRotation = null;
}

comp_Transform::comp_Transform( Vector2D& start, double scale) : Component()
{
	this->position = new Vector2D(start);
	centerOfRotation = null;
	this->scale = scale;
	this->rotation = 0;
}

comp_Transform::comp_Transform( double X, double Y, double scale) : Component()
{
	this->position = new Vector2D(X, Y);
	centerOfRotation = null;
	this->scale = scale;
	this->rotation = 0;
}

comp_Transform::~comp_Transform(){
	if (this->position != null)
	{
		delete this->position;
		this->position = null;
	}
	if (this->centerOfRotation != null)
	{
		delete this->centerOfRotation;
		this->centerOfRotation = null;
	}
}

void comp_Transform::setPosition(double X, double Y)
{
	this->position->Set(X,Y);
}

double comp_Transform::rotationDegrees()
{
	return RadToDeg(this->rotation);
}

void comp_Transform::rotateBy(double radians)
{
	this->rotation += radians;
}

void comp_Transform::rotateByDegrees(double degrees)
{
	this->rotation += DegToRad(degrees);
}

double comp_Transform::RadToDeg(double rad)
{
	return rad * 180 / M_PI;
}

double comp_Transform::DegToRad(double deg)
{
	return deg * M_PI / 180;
}

void comp_Transform::setCenterOfRotation(int x, int y)
{
	if (centerOfRotation == null)
	{
		centerOfRotation = new Vector2D(x, y);
	}
	else
	{
		centerOfRotation->Set(x, y);
	}
}

Vector2D* comp_Transform::getCenterOfRotation() const
{
	if (centerOfRotation == null){
		return null;
	}
	else{
		return centerOfRotation;
	}
}

SDL_Point* comp_Transform::getCenterOfRotation_SDL() const
{
	if (centerOfRotation == null)
	{
		return null;
	}
	else
	{
		SDL_Point* cor = new SDL_Point();
		cor->x = centerOfRotation->X;
		cor->y = centerOfRotation->Y;
		return cor;
	}
}

Vector2D* comp_Transform::getCenterOfMass() const
{
		Vector2D* com = new Vector2D();
		com->X = width/2;
		com->Y = height/2;
		return com;
}

SDL_Point* comp_Transform::getCenterOfMass_SDL() const
{
	SDL_Point* com = new SDL_Point();
	com->x = width / 2;
	com->y = height / 2;
	return com;
}