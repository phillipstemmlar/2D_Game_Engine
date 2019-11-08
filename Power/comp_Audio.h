#pragma once

#ifndef COMP_AUDIO_H
#define COMP_AUDIO_H

#include "Power.h"

class comp_Audio : public Component
{
private:
	std::unordered_map<string, SoundEffect*> sounds;
	std::vector<string> names;
public:
	comp_Audio();
	~comp_Audio();

	void addSound(string soundName, string fileName, unsigned int loop = 1);

	//remove sound and music by calling go.destroy();

	void play(string soundName);
	void pause(string soundName);
	void stop(string soundName);
	void toggle(string soundName);
	void restart(string soundName);

	void setVolume(string soundName, int Volume);
	int getVolume(string soundName);
};

#endif