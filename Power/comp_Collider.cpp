#include "Power.h"
#include "comp_Collider.h"

int comp_Collider::count = 0;

comp_Collider::comp_Collider() : Component()
{
	box = new SDL_Rect();
	handler = null;

	drawing = true;
	enabled = true;
	future = false;
	setDrawColor(0,255,0);
	setDefaultDrawColor(0,255,0);
	id = count++;

	Game::colManager->addCollider(this);
}

comp_Collider::~comp_Collider()
{
	if (box) { delete box; box = null; }
	if (handler != null) { delete handler; handler = null; }
}

void comp_Collider::Init()
{
	scale = Owner->getComponent<comp_Transform>().scale;

	box->x = Owner->getComponent<comp_Transform>().position->X;
	box->y = Owner->getComponent<comp_Transform>().position->Y;

	box->w = Owner->getComponent<comp_Transform>().width;
	box->h = Owner->getComponent<comp_Transform>().height;
}

void comp_Collider::Update(double deltaTime)
{
	box->x = Owner->getComponent<comp_Transform>().position->X;
	box->y = Owner->getComponent<comp_Transform>().position->Y;

	box->w = Owner->getComponent<comp_Transform>().width;
	box->h = Owner->getComponent<comp_Transform>().height;
}

void comp_Collider::Draw()
{
	if (drawing && enabled)
	{
		SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(Game::renderer, box);
	}
	color = defaultColor;
}

void comp_Collider::useFutureCollision()
{
	future = true;
}

void comp_Collider::noFutureCollision()
{
	future = false;
}

bool comp_Collider::getFutureCollision()
{
	return future;
}


void comp_Collider::handleCollision(Collision* col)
{
	if (handler != null)
	{
		handler->onCollision(col);
		if (col) {
			delete col;
		}
	}
}

bool comp_Collider::hasHandler()
{
	return (handler != null);
}

void comp_Collider::setHandler(CollisionHandler* handle)
{
	handler = handle;
}


int comp_Collider::getID() const
{
	return id;
}

void comp_Collider::setDrawColor(int r, int g, int b, int a )
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void comp_Collider::setDefaultDrawColor(int r, int g, int b, int a)
{
	defaultColor.r = r;
	defaultColor.g = g;
	defaultColor.b = b;
	defaultColor.a = a;
}

void comp_Collider::setDrawing(bool D)
{
	drawing = D;
}

void comp_Collider::Enable()
{
	enabled = true;
}

void comp_Collider::Disable()
{
	enabled = false;
}

SDL_Rect comp_Collider::getBox() const
{
	return *box;
}