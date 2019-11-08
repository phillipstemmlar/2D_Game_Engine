#pragma once

#ifndef INPUT_HANLDER_H
#define INPUT_HANLDER_H

#include "Power.h"

class comp_Input;

class InputHandler
{
protected:
	comp_Input* input;
public:
	InputHandler(comp_Input* in) { input = in; };
	~InputHandler() {};

	virtual void Input() {}
};

#endif