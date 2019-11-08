#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Power.h"

class Animation
{
public:
	Animation(string name, string filename, int fIndex, int fCount, int fWidth, int fHeight);
	~Animation();

	string Name;

	SDL_Texture* texture;
	SDL_Rect** frames;

	double fps;
	string fileName;

	int frameWidth;
	int frameHeigh;
	int textWidth;
	int textHeight;

	int firstIndex;
	int frameCount;

	bool Loop;

	SDL_RendererFlip flipped;

	void setFrameSize(int w, int h);
	void setFlipped(SDL_RendererFlip flip);
	void loadTexture();
};

#endif