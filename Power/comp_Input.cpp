#include "Power.h"
#include "comp_Input.h"


comp_Input::comp_Input()
{
	Game::inputManager->addInput(this);

	keyboardState = SDL_GetKeyboardState(&keyboardLength);
	mouseState = 0;

	prev_keyboardState = null;
	prev_mouseState = 0;

	handler = null;
}

comp_Input::~comp_Input()
{
	if (prev_keyboardState) { delete [] prev_keyboardState; prev_keyboardState = null; }
	if (handler != null) { delete handler; handler = null; }
}

void comp_Input::handelInput(const Uint8* keyboardState, const Uint32 mouseState)
{
	this->keyboardState = keyboardState;
	this->mouseState = mouseState;
	Input();
	if (prev_keyboardState == null) { prev_keyboardState = new Uint8[keyboardLength]; }
	memcpy(prev_keyboardState,this->keyboardState, keyboardLength);
	prev_mouseState = this->mouseState;
}

bool comp_Input::hasHandler()
{
	return (handler != null);
}

void comp_Input::setHandler(InputHandler* handle)
{
	handler = handle;
}

void comp_Input::Input()
{
	if (handler != null)
	{
		handler->Input();
	}
}

bool comp_Input::onClick(int button)
{
	return ( mouseState & SDL_BUTTON(button) );
}

bool comp_Input::onClickDown(int button)
{
	return !(prev_mouseState & SDL_BUTTON(button))&&(mouseState & SDL_BUTTON(button));
}

bool comp_Input::onClickUp(int button)
{
	return (prev_mouseState & SDL_BUTTON(button)) && !(mouseState & SDL_BUTTON(button));
}

bool comp_Input::onKeyPressed(int key)
{
	return (keyboardState[key]);
}

bool comp_Input::onKeyDown(int key)
{
	if (prev_keyboardState == null) { return false; }
	return !(prev_keyboardState[key])&&(keyboardState[key]);
}

bool comp_Input::onKeyUp(int key)
{
	if (prev_keyboardState == null) { return false; }
	return (prev_keyboardState[key])&&!(keyboardState[key]);
}