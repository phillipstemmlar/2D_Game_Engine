#include "Power.h"
#include "Collision.h"


Collision::Collision(comp_Rigidbody* rigid, comp_Collider* coldr)
{
	RigidBody = rigid;
	other = coldr;
}


Collision::~Collision()
{
}
