#include "Power.h"
#include "comp_Rigidbody.h"


comp_Rigidbody::comp_Rigidbody() : Component()
{
	setGravityConst(_g);

	torque = 0;
	angularAcceleration = 0;
	angularVelocity = 0;

	mass = 1;
	maxSpeed = 10.0 * _m;

	Game::colManager->addRigidbody(this);
}

comp_Rigidbody::~comp_Rigidbody()
{

}

void comp_Rigidbody::Update(double deltaTime)
{
	double dt = deltaTime * _m;
	position.Set(*Owner->getComponent<comp_Transform>().position);

	applyForce(gravity);

	acceleration = force / mass;
	angularAcceleration = torque / rotInertia();

	velocity += acceleration * dt;
	angularVelocity += angularAcceleration * deltaTime;
	
	/**/
	velocity.clampMagnitude(maxSpeed);
	angularVelocity = (abs(angularVelocity) > maxRotationSpeed) ? ((angularVelocity > 0) ? maxRotationSpeed : -1*maxRotationSpeed)  : angularVelocity;
	/**/

	position += velocity * dt;
	angularPosition += angularVelocity * deltaTime;

	Owner->getComponent<comp_Transform>().position->Set(position);

	force.Set(0, 0);
	torque = 0;
}

Vector2D comp_Rigidbody::getGravity()
{
	return gravity;
}

double comp_Rigidbody::getGravityConst() const
{
	return gravityConst;
}

void comp_Rigidbody::setGravityConst(double a)
{
	gravityConst = a;

	gravity.Set( Vector2D::DOWN() );
	gravity *= gravityConst;
}

void comp_Rigidbody::applyForce(Vector2D F)
{
	force += F;
}

void comp_Rigidbody::applyTorque(double T)
{
	torque += T;
}

void comp_Rigidbody::setMaxSpeed(double speed)
{
	maxSpeed = speed;
}

double comp_Rigidbody::getMaxSpeed()
{
	return maxSpeed;
}

void comp_Rigidbody::setMaxRotSpeed(double rotSpeed)
{
	maxRotationSpeed = rotSpeed;
}

double comp_Rigidbody::getMaxRotSpeed()
{
	return maxRotationSpeed;
}

double comp_Rigidbody::rotInertia()
{
	/*
	Vector2D* cor = Owner->getComponent<comp_Transform>().getCenterOfRotation();
	Vector2D* com = Owner->getComponent<comp_Transform>().getCenterOfMass();
	
	double x = com->X - cor->X;
	double y = com->Y - cor->Y;

	Vector2D temp(x,y);

	*/
	double w = Owner->getComponent<comp_Transform>().width;
	double h = Owner->getComponent<comp_Transform>().height;
	return 0.083333333333*mass*(w*w + h * h);
}

void comp_Rigidbody::print()
{
	Log("=====================================");
	std::cout << "Force: " << force << std::endl;
	std::cout << "Accel: " << acceleration << std::endl;
	std::cout << "Vel:   " << velocity << std::endl;
	std::cout << "Pos:   " << position << std::endl;
	Log("=====================================");
}