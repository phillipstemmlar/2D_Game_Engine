#pragma once
class MusicEffect
{
private:
	Mix_Music* music;
	unsigned int loops;		//0 is infinit loop

	static int count;
	int id;

public:
	MusicEffect(string fileName, int loops = 1);
	~MusicEffect();

	void play();
	void pause();
	void stop();
	void toggle();
	void restart();
};

