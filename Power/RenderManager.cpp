#include "Power.h"
#include "RenderManager.h"
#include "Game.h"

RenderManager::RenderManager()
{
	renderer = Game::renderer;
}

RenderManager::~RenderManager()
{
	renderer = null;

	while (rendComps.size() > 0)
	{
		rendComps.pop_back();
	}

}

void RenderManager::Draw()
{
	SDL_SetRenderDrawColor(renderer, BG_Color.r, BG_Color.g, BG_Color.b, BG_Color.a);
	SDL_RenderClear(renderer);

	DrawRenderComponents();
	Game::colManager->Draw();
	DrawDrawables();

	SDL_RenderPresent(renderer);
}

void RenderManager::DrawRenderComponents()
{
	for (int i = 0; i < rendComps.size(); i++)
	{
		if(rendComps[i] == null || rendComps[i]->Owner->getState() == EDead)
		{
			rendComps.erase(rendComps.begin() + i);
			i--;
		}
		else if (rendComps[i]->Owner->getState() == EActive)
		{
			 rendComps[i]->Draw();
		}
	}
}

void RenderManager::DrawDrawables()
{
	for (int i = 0; i < drawables.size(); i++)
	{
		if (drawables[i] != null )
		{
			drawables[i]->DrawItem(renderer);
		}
		else {
			drawables.erase(drawables.begin() + i);
			i--;
		}
	}
}

void RenderManager::addRenderComponent(comp_Sprite* obj)
{
	int order = obj->getDrawOrder();

	auto iter = rendComps.begin();

	for (; iter != rendComps.end(); iter++)
	{
		if (order < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	rendComps.insert(iter,obj);
}

void RenderManager::addDrawable(Drawable* D)
{
	drawables.push_back(D);
}

void RenderManager::removeDrawable(int id)
{
	for (int i = 0; i < drawables.size(); i++)
	{
		if (drawables[i] != null && drawables[i]->getID() == id)
		{
			drawables.erase(drawables.begin() + i);
			i--;
		}
	}
}

SDL_Texture* RenderManager::LoadTexture(string filename)		//satic
{
	SDL_Surface* surf = IMG_Load(filename.c_str());	
	if (!surf)
	{
		SDL_Log("Failed to load Texture from file: %s", filename);
		return null;
	}
	SDL_Texture* text = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);
	if (!text)
	{
		SDL_Log("Failed to convert Surface to Texture: %s", filename);
		return null;
	}

	std::cout << "Asset loadded successfully: " << filename << std::endl;

	return text;
}

void RenderManager::setBGcolor(int r, int g, int b, int a)
{
	BG_Color.r = r;
	BG_Color.g = g;
	BG_Color.b = b;
	BG_Color.a = a;
}
