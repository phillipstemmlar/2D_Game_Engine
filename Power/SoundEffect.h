#pragma once
class SoundEffect
{
private:

	Mix_Chunk* chunk;
	unsigned int loops;		//0 is infinit loop
	int Volume;

	static int count;
	int id;

public:
	SoundEffect(string fileName, unsigned  int loops = 1);
	~SoundEffect();

	void play();
	void pause();
	void stop();
	void toggle();
	void restart();

	void setVolume(int volume);
	int getVolume();
};

