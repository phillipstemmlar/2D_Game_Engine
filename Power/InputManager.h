#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Power.h"

class Game;
class comp_Input;

class InputManager
{
private:
	std::vector<comp_Input*> inputs;
	Game* game;

	void handleComponentInput(const Uint8* keyboardState, const Uint32 mouseState);
public:
	InputManager(Game* G);
	~InputManager();

	int mouseX;
	int mouseY;

	void addInput(comp_Input* input);
	void Input();
	void Update(double deltaTime);
};

#endif