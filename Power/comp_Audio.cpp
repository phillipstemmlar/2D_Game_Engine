#include "Power.h"
#include "comp_Audio.h"

comp_Audio::comp_Audio()
{
}


comp_Audio::~comp_Audio()
{
	//remove all soundEffects + delete

	for (int i = 0; i < names.size(); i++)
	{
		sounds[names[i]]->stop();
		SoundEffect* snd = sounds[names[i]];
		sounds.erase(names[i]);
		names.erase(names.begin() + i);

		if (snd != null) 
		{
			delete snd;
			snd = null;
		}
	}

}

void comp_Audio::addSound(string soundName, string fileName, unsigned int loop)
{
	sounds.emplace(soundName, new SoundEffect(fileName, loop));
	names.push_back(soundName);
}

void comp_Audio::play(string soundName)
{
	sounds[soundName]->play();
}

void comp_Audio::pause(string soundName)
{
	sounds[soundName]->pause();
}


void comp_Audio::stop(string soundName)
{
	sounds[soundName]->stop();
}

void comp_Audio::toggle(string soundName)
{
	sounds[soundName]->toggle();
}

void comp_Audio::restart(string soundName)
{
	sounds[soundName]->restart();
}

void comp_Audio::setVolume(string soundName, int Volume)
{
	sounds[soundName]->setVolume(Volume);
}

int comp_Audio::getVolume(string soundName)
{
	return sounds[soundName]->getVolume();
}