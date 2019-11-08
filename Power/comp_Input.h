#pragma once

#ifndef COMP_INPUT_H
#define COMP_INPUT_H

#include "Power.h"

class Game;
class InputManager;
class InputHandler;

class comp_Input : public Component
{
private:
	const Uint8* keyboardState;
	Uint32 mouseState;

	Uint8* prev_keyboardState;
	Uint32 prev_mouseState;

	InputHandler* handler;

	int keyboardLength;

	bool holding = false;

	void Input();

public:
	comp_Input();
	~comp_Input();

	bool onClick(int button);
	bool onClickDown(int button);
	bool onClickUp(int button);

	bool onKeyPressed(int key);
	bool onKeyDown(int key);
	bool onKeyUp(int key);

	bool hasHandler();
	void setHandler(InputHandler* handle);

	void handelInput(const Uint8* keyboardState, const Uint32 mouseState);
};

#endif