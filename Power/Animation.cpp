#include "Power.h"
#include "Animation.h"

const double defaultFPS = 24;

Animation::Animation(string name, string filename, int fIndex, int fCount, int fWidth, int fHeight)
{
	Name = name;
	fileName = filename;

	firstIndex = fIndex;
	frameCount = fCount;

	setFrameSize(fWidth, fHeight);

	fps = defaultFPS;
	flipped = SDL_FLIP_NONE;

	Loop = true;

	texture = null;
	frames = null;
	loadTexture();
}

Animation::~Animation()
{
	if (texture != null) { delete texture; texture = null; }
	if (frames != null)
	{
		for (int i = 0; i < frameCount; i++)
		{
			if (frames[i] != null)
			{
				delete frames[i];
				frames[i] = null;
			}
		}
		delete[] frames;
		frames = null;
	}
}

void Animation::setFrameSize(int w, int h)
{
	frameWidth = w;
	frameHeigh = h;
}

void Animation::setFlipped(SDL_RendererFlip flip)
{
	flipped = flip;
}

void Animation::loadTexture()
{
	texture = RenderManager::LoadTexture(fileName.c_str());

	if (!texture) { return; textWidth = textHeight = 0.0; }

	SDL_QueryTexture(texture, null, null, &textWidth, &textHeight);

	if (frames != null){
		for (int i = 0; i < frameCount; i++){
			if (frames[i] != null){
				delete frames[i];
				frames[i] = null;
			}
		}
		delete[] frames;
		frames = null;
	}

	frames = new SDL_Rect*[frameCount];
	for (int i = 0; i < frameCount; i++)
	{
		int x = (firstIndex + i) % (textWidth/frameWidth);
		int y = (firstIndex + i) / (textWidth / frameWidth);
		frames[i] = new SDL_Rect{ x * frameWidth, y * frameHeigh, frameWidth, frameHeigh };
	}

}

