#include "Power.h"
#include "SoundEffect.h"

int SoundEffect::count = 0;

SoundEffect::SoundEffect(string fileName, unsigned int loops)
{
	chunk = Mix_LoadWAV(fileName.c_str());
	this->loops = loops;
	Volume = MIX_MAX_VOLUME;

	id = count;
	count++;
	
	std::cout << "Sound File loaded successfully: " << fileName << std::endl;
}

SoundEffect::~SoundEffect()
{
	stop();
	Mix_FreeChunk(chunk);
}

void SoundEffect::play()
{
	if (!Mix_Playing(id)) {
		Mix_PlayChannel(id, chunk, loops - 1);
	}
	else if (Mix_Paused(id))
	{
		Mix_Resume(id);
	}
}

void SoundEffect::pause()
{
	if (Mix_Playing(id))
	{
		Mix_Pause(id);
	}
}

void SoundEffect::stop()
{
	Mix_HaltChannel(id);
}

void SoundEffect::toggle()
{
	if (!Mix_Playing(id)) {
		Mix_PlayChannel(id, chunk, loops - 1);
	}
	else if (Mix_Paused(id))
	{
		Mix_Resume(id);
	}
	else
	{
		Mix_Pause(id);
	}
}

void SoundEffect::restart()
{
	stop();
	play();
}

void SoundEffect::setVolume(int volume)
{
	volume = (volume < 0) ? 0 : volume;
	Mix_Volume(id, volume);
}

int SoundEffect::getVolume()
{
	return Mix_Volume(id,-1);
}
