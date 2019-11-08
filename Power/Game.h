#pragma once

#ifndef GAME_H
#define GAME_H

#include "Power.h"

class GameObjectManager;
class RenderManager;
class CollisionManager;
class EventManager;
class InputManager;
class AudioManager;
class MusicManager;

class Game
{
public:
	Game(int W = 800, int H = 600);
	~Game();

	bool INITIALIZE();
	void RUN();
	void SHUTDOWN();

	void quit();
	void setBGcolor(int r, int g, int b, int a = 255);

	static int winWidth;
	static int winHeight;

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static GameObjectManager* goManager;
	static RenderManager* rendManager;
	static CollisionManager* colManager;
	static EventManager* eventManager;
	static InputManager* inputManager;
	static MusicManager* musicManager;

private:
	bool isRunning;
	double TicksCount;

protected:
	void INPUT();
	void UPDATE();
	void OUTPUT();

	virtual void Setup();

	void addGameObject(GameObject* obj);

};

#endif

