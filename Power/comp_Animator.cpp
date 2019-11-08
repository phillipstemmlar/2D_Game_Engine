#include "Power.h"
#include "comp_Animator.h"


comp_Animator::comp_Animator() : Component()
{
	defaultAnimation = "";
	currentAnimation = "";
	nextAnimation = "";
	currentFrame = 0.0;
}


comp_Animator::~comp_Animator()
{
	for (int i = 0; i < animNames.size(); i++)
	{
		Animations.erase(animNames[i]);
	}
	animNames.clear();
}

void comp_Animator::Update(double deltaTime)
{
	if (!Animations.empty())
	{
		currentFrame += Animations[currentAnimation]->fps * deltaTime;

		//loop frame
		if (Animations[currentAnimation]->Loop)
		{
			while ( currentFrame >= Animations[currentAnimation]->frameCount )
			{
				currentFrame -= Animations[currentAnimation]->frameCount;
			}
		}
		else if(currentFrame >= Animations[currentAnimation]->frameCount)
		{
			stop();
		}

		transitionRules();
	}
}

void comp_Animator::transition(string AnimationName)
{
	if (currentAnimation != AnimationName) {
		currentAnimation = AnimationName;
		currentFrame = 0;
	}
}

void comp_Animator::restart()
{
	currentFrame = 0;
}

void comp_Animator::stop()
{
	transition(defaultAnimation);
}

void comp_Animator::AddAnimation(string name, string filename, int fIndex, int fCount, int fWidth, int fHeight)
{
	if (Animations.count(name) > 0) { std::cout << "Animation with that name already exists: " << name << std::endl; return; }

	bool first = false;
	if (Animations.empty())
	{
		first = true;
	}

	Animation* anim = new Animation(name, filename, fIndex, fCount, fWidth, fHeight);
	Animations.insert_or_assign(name, anim);
	animNames.push_back(name);

	if (first)
	{
		setDefaultAnimation(name);
		transition(name);
	}
}

void comp_Animator::removeAnimation(string name)
{
	Animation* remAnim = Animations[name];
	Animations.erase(name);
	if (remAnim)
	{
		delete remAnim;
		remAnim = null;
	}
	
	for (int i = 0; i < animNames.size(); i++)
	{
		if (animNames[i] == name)
		{
			animNames.erase(animNames.begin() + i);
			return;
		}
	}
}

void comp_Animator::setDefaultAnimation(string name)
{
	defaultAnimation = name;
}

string comp_Animator::getCurrentAnimationName() const
{
	return currentAnimation;
}

SDL_Texture* comp_Animator::Texture()
{
	//std::cout << "				NAME: " << Animations[currentAnimation]->Name << std::endl;
	return Animations[currentAnimation]->texture;
}

SDL_Rect* comp_Animator::Frame()
{
	return Animations[currentAnimation]->frames[static_cast<int>(currentFrame)];
}

SDL_RendererFlip comp_Animator::Flipped()
{
	return  Animations[currentAnimation]->flipped;
}

void comp_Animator::setLoop(string name, bool val)
{
	Animations[name]->Loop = val;
}

void comp_Animator::setFlipped(string name,SDL_RendererFlip flip)
{
	Animations[name]->flipped = flip;
}

SDL_RendererFlip comp_Animator::getFlipped(string name)
{
	return Animations[name]->flipped;
}

void comp_Animator::setFPS(string name, double fps)
{
	Animations[name]->fps = fps;
}

void comp_Animator::transitionRules()
{

}
