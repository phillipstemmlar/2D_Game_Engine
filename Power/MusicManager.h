#pragma once

#include "Power.h"
#include "MusicEffect.h"

class MusicManager
{
private:
	std::unordered_map<string, MusicEffect*> musicSounds;
	string currentMusic;

	int Volume;

public:
	MusicManager();
	~MusicManager();

	void addMusic(string musicName, string fileName, int loops = 1);		//-1 => infinite

	void play(string musicName);
	void play();
	void pause();
	void stop();
	void toggle();
	void restart();

	void setVolume(int Volume);
	int getVolume();
};

