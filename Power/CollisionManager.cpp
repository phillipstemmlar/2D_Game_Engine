#include "Power.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	while (Colliders.size() > 0)
	{
		Colliders.pop_back();
	}

	while (RigidBodies.size() > 0)
	{
		RigidBodies.pop_back();
	}

}

void CollisionManager::Update(double deltaTime)
{
	checkCollisions();
	handleCollisions();
}

void CollisionManager::checkCollisions()
{
	for (int i = 0; i < RigidBodies.size(); i++)
	{
		if (RigidBodies[i] == null || RigidBodies[i]->Owner->getState() == EDead)
		{
			RigidBodies.erase(RigidBodies.begin() + i);
			i--;
		}
		else if (RigidBodies[i]->Owner->getState() == EActive)
		{
			for (int n = 0; n < Colliders.size(); n++)
			{
				bool collides = false;

				if(RigidBodies[i]->Owner->getComponent<comp_Collider>().getFutureCollision()){
					collides = AABB_future(RigidBodies[i], Colliders[n]);
				}else{
					collides = AABB(RigidBodies[i], Colliders[n]);
				}

				if (collides){
					newCollision(RigidBodies[i], Colliders[n]);
				}
			}
		}
	}
}


void CollisionManager::handleCollisions()
{
	while (!Collisions.isEmpty())
	{
		Collision* col  = Collisions.pop();
		if (col->RigidBody->Owner->getComponent<comp_Collider>().hasHandler() ) {
			col->RigidBody->Owner->getComponent<comp_Collider>().handleCollision(col);
		}
	}
}

void CollisionManager::newCollision(comp_Rigidbody* rigid, comp_Collider* col)
{
	Collision* newCol = new Collision(rigid, col);
	Collisions.push(newCol);
	//Log("Collision Added to Queue");
}

void CollisionManager::Draw()
{
	for (int i = 0; i < Colliders.size(); i++)
	{
		if (Colliders[i] == null || Colliders[i]->Owner->getState() == EDead)
		{
			Colliders.erase(Colliders.begin() + i);
			i--;
		}
		else if (Colliders[i]->Owner->getState() == EActive)
		{
			Colliders[i]->Draw();
		}
	}
}

void CollisionManager::addCollider(comp_Collider* obj)
{
	Colliders.push_back(obj);
}

void CollisionManager::addRigidbody(comp_Rigidbody* obj)
{
	RigidBodies.push_back(obj);
}

void CollisionManager::setAllColliderDrawColor(int r, int g, int b, int a )
{
	for (int i = 0; i < Colliders.size(); i++)
	{
		Colliders[i]->setDrawColor(r,g,b,a);
	}
}

bool CollisionManager::AABB(comp_Rigidbody* rigid, comp_Collider* col)
{/*
	comp_Collider* rig = & rigid->Owner->getComponent<comp_Collider>();

	double vx = rigid->velocity.X;
	double vy = rigid->velocity.Y;

	if (rig->getID() == col->getID()) { return false; }
	return  ((rig->getBox().x + vx + rig->getBox().w >= col->getBox().x && col->getBox().x + col->getBox().w >= rig->getBox().x + vx)
		|| (col->getBox().x + col->getBox().w <= rig->getBox().x + vx && rig->getBox().x + vx + rig->getBox().w <= col->getBox().x))
		&& ((rig->getBox().y + vy + rig->getBox().h >= col->getBox().y && col->getBox().y + col->getBox().h >= rig->getBox().y + vy)
			|| (col->getBox().y + col->getBox().h <= rig->getBox().y + vy && rig->getBox().y + vy + rig->getBox().h <= col->getBox().y));
	*/
	return AABB(&rigid->Owner->getComponent<comp_Collider>(), col);
}

bool CollisionManager::AABB(comp_Collider* col1, comp_Collider* col2)
{
	if (col1->getID() == col2->getID()) { return false; }
	return  (  (col1->getBox().x  + col1->getBox().w >= col2->getBox().x && col2->getBox().x + col2->getBox().w >= col1->getBox().x)
			|| (col2->getBox().x  + col2->getBox().w <= col1->getBox().x && col1->getBox().x + col1->getBox().w <= col2->getBox().x))
			&& ((col1->getBox().y + col1->getBox().h >= col2->getBox().y && col2->getBox().y + col2->getBox().h >= col1->getBox().y)
			|| (col2->getBox().y  + col2->getBox().h <= col1->getBox().y && col1->getBox().y + col1->getBox().h <= col2->getBox().y));
}

bool CollisionManager::AABB_future(comp_Rigidbody* rigid, comp_Collider* col)
{
	comp_Collider* rig = & rigid->Owner->getComponent<comp_Collider>();

	double vx = rigid->velocity.X;
	double vy = rigid->velocity.Y;

	if (rig->getID() == col->getID()) { return false; }
	return  ((rig->getBox().x + vx + rig->getBox().w >= col->getBox().x && col->getBox().x + col->getBox().w >= rig->getBox().x + vx)
		|| (col->getBox().x + col->getBox().w <= rig->getBox().x + vx && rig->getBox().x + vx + rig->getBox().w <= col->getBox().x))
		&& ((rig->getBox().y + vy + rig->getBox().h >= col->getBox().y && col->getBox().y + col->getBox().h >= rig->getBox().y + vy)
			|| (col->getBox().y + col->getBox().h <= rig->getBox().y + vy && rig->getBox().y + vy + rig->getBox().h <= col->getBox().y));

}

bool CollisionManager::lineCollision(Line2D line, Queue<comp_Collider*> cols)
{
	bool collides = false;
	for (int i = 0; i < Game::colManager->Colliders.size(); i++)
	{
		collides = false;

		SDL_Rect rect = Game::colManager->Colliders[i]->getBox();

		if ( line.intersects(rect) ) {
			collides = true;
			cols.push(Game::colManager->Colliders[i]);
		}
	}
	return collides;
}

bool CollisionManager::lineCollision(const Line2D & line, Queue<comp_Collider*> cols, string filterTag)
{
	bool collides = false;
	for (int i = 0; i < Game::colManager->Colliders.size(); i++)
	{
		collides = false;
		
		if (Game::colManager->Colliders[i]->Owner->Tag == filterTag)
		{
			SDL_Rect rect = Game::colManager->Colliders[i]->getBox();

			double x = Game::colManager->Colliders[i]->getBox().x;
			double y = Game::colManager->Colliders[i]->getBox().y;
			double w = Game::colManager->Colliders[i]->getBox().w;
			double h = Game::colManager->Colliders[i]->getBox().h;

			std::cout << "Coll: (" << x << "," << y << ") "<< w << " : " << h << std::endl;
			std::cout << "Line: " << line.toString() << std::endl;

			if (line.intersects(rect)) {
				collides = true;
				cols.push(Game::colManager->Colliders[i]);
			}
		}
	}
	return collides;
}
