#pragma once

#ifndef COMP_SPRITE_H
#define COMP_SPRITE_H

#include "Power.h"

class comp_Transform;

class comp_Sprite : public Component
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* defaultTexture;

	Vector2D position;
	double width;
	double height;
	double angleDeg;
	double scale;

	double WinHeight;
	double WinWidth;

	int DrawOrder;

	string fileName;

	SDL_Texture* texture;
	SDL_Rect* drawRect;

public:
	comp_Sprite(int order = 100);
	comp_Sprite(string filename, int order = 100);
	~comp_Sprite();

	void Init();
	void Draw();

	int getDrawOrder() const;

	void loadTexture(string filename);
};

#endif