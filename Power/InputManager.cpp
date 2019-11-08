#include "Power.h"
#include "InputManager.h"

InputManager::InputManager(Game* G)
{
	game = G;
}

InputManager::~InputManager()
{
	while (inputs.size() > 0)
	{
		inputs.pop_back();
	}
}

void InputManager::Input()
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			game->quit();
		}
	}

	handleComponentInput(keyboardState, mouseState);

	//Maybe Remove later
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		game->quit();
	}

	SDL_PumpEvents();
}

void InputManager::handleComponentInput(const Uint8* keyboardState, const Uint32 mouseState)
{
	for (int i = 0; i < inputs.size(); i++)
	{
		if (inputs[i] != null && inputs[i]->Owner->getState() == EActive)
		{
			inputs[i]->handelInput(keyboardState, mouseState);
		}
		else if (inputs[i]->Owner->getState() == EDead)
		{
			inputs.erase(inputs.begin() + i);
		}
	}
}

void InputManager::addInput(comp_Input* input)
{
	inputs.push_back(input);
}

void InputManager::Update(double deltaTime)
{
	Input();
}
