#pragma once

#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "Power.h"

class comp_Sprite;
class Drawable;

class RenderManager
{
private:
	std::vector<comp_Sprite*> rendComps;
	std::vector<Drawable*> drawables;
	SDL_Renderer* renderer;
	SDL_Color BG_Color;
protected:
	void DrawRenderComponents();
	void DrawDrawables();
public:
	RenderManager();
	~RenderManager();

	void Draw();
	void addRenderComponent(comp_Sprite* obj);			//remove by calling go.Destroy();
	
	void addDrawable(Drawable* D);
	void removeDrawable(int id);

	static SDL_Texture* LoadTexture(string filename);

	void setBGcolor(int r, int g, int b, int a = 255);
};

#endif