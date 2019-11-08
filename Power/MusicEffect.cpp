#include "Power.h"
#include "MusicEffect.h"


int MusicEffect::count = 0;

MusicEffect::MusicEffect(string fileName, int loops)
{
	music = Mix_LoadMUS(fileName.c_str());
	this->loops = (loops < 0)? -1 : loops;
	id = count;
	count++;

	std::cout << "Music File loaded successfully: " << fileName << std::endl;
}

MusicEffect::~MusicEffect()
{
	stop();
	Mix_FreeMusic(music);
}

void MusicEffect::play()
{
	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, loops);
	}
	else if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void MusicEffect::pause()
{
	if (Mix_PlayingMusic())
	{
		Mix_PauseMusic();
	}
}

void MusicEffect::stop()
{
	Mix_HaltMusic();
}

void MusicEffect::toggle()
{
	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, loops);
	}
	else if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}

void MusicEffect::restart()
{
	stop();
	play();
}
