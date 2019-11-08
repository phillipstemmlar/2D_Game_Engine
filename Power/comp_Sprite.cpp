#include "Power.h"
#include "comp_Sprite.h"

comp_Sprite::comp_Sprite(int order) : Component()
{

	renderer = Game::renderer;
	DrawOrder = order;
	Game::rendManager->addRenderComponent(this);
	defaultTexture = null;
	width = 0;
	height = 0;
}

comp_Sprite::comp_Sprite(string filename, int order) : Component()
{
	renderer = Game::renderer;
	DrawOrder = order;
	Game::rendManager->addRenderComponent(this);
	defaultTexture = null;
	loadTexture(filename);
}


comp_Sprite::~comp_Sprite(){
	delete drawRect;
}

void comp_Sprite::Init()
{
	WinWidth = Game::winWidth;
	WinHeight = Game::winHeight;

	position = *(Owner->getComponent<comp_Transform>().position);
	scale = Owner->getComponent<comp_Transform>().scale;
	angleDeg = Owner->getComponent<comp_Transform>().rotationDegrees();
}

void comp_Sprite::Draw()
{	
	if (!renderer) { Log("Cannot Draw Sprite: No Renderer. \n"); return; }

	texture = null;
	drawRect = null;
	SDL_RendererFlip flip;

	//if (Owner->hasComponent<comp_Animator>())
	if(true)
	{
		texture = Owner->getComponent<comp_Animator>().Texture();
		drawRect = Owner->getComponent<comp_Animator>().Frame();

		//drawRect = new SDL_Rect{ 0, 0, 32, 48};

		width = drawRect->w;
		height = drawRect->h;

		//std::cout << drawRect->x << " , " << drawRect->y << "			";
		//std::cout << drawRect->w << " , " << drawRect->h << std::endl;

		flip = Owner->getComponent<comp_Animator>().Flipped();


		if (texture == null)
		{
			SDL_Log("Cannot draw sprite, Animation Texture is null: %s.", Owner->getComponent<comp_Animator>().getCurrentAnimationName() );
			return;
		}
	}
	else if(defaultTexture == null)
	{
		SDL_Log("Cannot draw sprite, default Texture is null: %s.", fileName);
		return;
	}
	else
	{
		texture = defaultTexture;
		//texture = Owner->getComponent<comp_Animator>().Texture();
		drawRect = null;
		flip = SDL_FLIP_NONE;
	}

	position = *(Owner->getComponent<comp_Transform>().position);
	scale = Owner->getComponent<comp_Transform>().scale;
	angleDeg = Owner->getComponent<comp_Transform>().rotationDegrees();

	SDL_Point* point = Owner->getComponent<comp_Transform>().getCenterOfRotation_SDL();

	double W = width * scale;
	double H = height * scale;

	Owner->getComponent<comp_Transform>().width = W;
	Owner->getComponent<comp_Transform>().height = H;

	SDL_Rect rendRect{ position.X, position.Y, W, H };

	SDL_RenderCopyEx(
		renderer,
		texture,
		drawRect,
		&rendRect,
		angleDeg,
		point,
		flip
	);

	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(renderer, &drawRect);
}

void comp_Sprite::loadTexture(string filename)
{
	if (defaultTexture != null) { delete defaultTexture; defaultTexture = null; }

	defaultTexture = RenderManager::LoadTexture(filename.c_str());

	if (defaultTexture == null) { return; width = height = 0.0; }

	fileName = filename;
	int w, h;
	SDL_QueryTexture(defaultTexture, null, null, &w, &h);
	width = w;
	height = h;
}

int comp_Sprite::getDrawOrder() const
{
	return DrawOrder;
}
