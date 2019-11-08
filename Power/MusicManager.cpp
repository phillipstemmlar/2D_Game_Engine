#include "Power.h"
#include "MusicManager.h"


MusicManager::MusicManager()
{
	currentMusic = "";
	Volume = MIX_MAX_VOLUME;
}


MusicManager::~MusicManager()
{
	//remove all MusicEffects + delete
}


void MusicManager::addMusic(string musicName, string fileName, int loops)
{
	musicSounds.emplace(musicName, new MusicEffect(fileName, loops));
}

void MusicManager::play(string musicName)
{
	if (musicName != currentMusic)
	{
		musicSounds[currentMusic]->stop();
		currentMusic = musicName;
	}
	musicSounds[currentMusic]->play();
}

void MusicManager::play()
{
	musicSounds[currentMusic]->play();
}

void MusicManager::pause()
{
	musicSounds[currentMusic]->pause();
}

void MusicManager::stop()
{
	musicSounds[currentMusic]->stop();
}

void MusicManager::toggle()
{
	musicSounds[currentMusic]->toggle();
}

void MusicManager::restart()
{
	musicSounds[currentMusic]->restart();
}

void MusicManager::setVolume(int volume)
{
	this->Volume = volume;
	volume = (volume < 0) ? 0 : volume;
	Mix_VolumeMusic(volume);
}

int MusicManager::getVolume()
{
	return this->Volume;
}
