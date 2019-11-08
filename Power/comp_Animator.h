#pragma once

#ifndef COMP_ANIMATOR_H
#define COMP_ANIMATOR_H

#include "ECS.h"
#include "Animation.h"

class Animation;

class comp_Animator : public Component
{
private:
	std::unordered_map<string, Animation*> Animations;
	std::vector<string> animNames;

	string currentAnimation;
	double currentFrame;

	string defaultAnimation;
	string nextAnimation;

public:
	comp_Animator();
	~comp_Animator();

	SDL_Texture* Texture();
	SDL_Rect* Frame();
	SDL_RendererFlip Flipped();

	void Update(double deltaTime);

	void AddAnimation(string name, string filename, int fIndex, int fCount, int fWidth, int fHeight);
	void removeAnimation(string name);

	void setDefaultAnimation(string name);
	string getCurrentAnimationName() const;
	
	void transition(string AnimationName);
	void stop();
	void restart();

	void setFlipped(string name, SDL_RendererFlip flip);
	void setLoop(string name, bool val);
	void setFPS(string name, double fps);

	SDL_RendererFlip getFlipped(string name);

	virtual void transitionRules();
};

#endif