#include "Power.h"
#include "Game.h"

SDL_Window* Game::window = null;
SDL_Renderer* Game::renderer = null;

GameObjectManager* Game::goManager = null;
RenderManager* Game::rendManager = null;
CollisionManager* Game::colManager = null;
EventManager* Game::eventManager = null;
InputManager* Game::inputManager = null;
MusicManager* Game::musicManager = null;

int Game::winWidth = 800;
int Game::winHeight = 600;

Game::Game(int W, int H)
{
	isRunning = false;

	Game::winWidth = W;
	Game::winHeight = H;

	goManager = null;
	rendManager = null;
	colManager = null;
}


Game::~Game()
{
	if (goManager != null) { delete goManager; goManager = null; }
	if (rendManager != null) { delete rendManager; rendManager = null; }
	if (colManager != null) { delete colManager; colManager = null; }
	if (eventManager != null) { delete eventManager; eventManager = null; }
	if (inputManager != null) { delete inputManager; inputManager = null; }
	if (musicManager != null) { delete musicManager; musicManager = null; }
}

bool Game::INITIALIZE()
{
	Log("Initializing game.");

	isRunning = true;
	TicksCount = 0;

	int sdlResult = SDL_Init(SDL_INIT_EVERYTHING);

	if (sdlResult != 0)	
	{
		SDL_Log("Unable to INIT SDL: %s",SDL_GetError() );
		return false;
	}

	int imgResult = IMG_Init(IMG_INIT_PNG);

	if (imgResult == 0)
	{
		SDL_Log("Unable to INIT SDL_image: %s", IMG_GetError());
		return false;
	}

	int mixResult = Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	if (mixResult == 0)
	{
		SDL_Log("Unable to INIT SDL_mixer: %s", Mix_GetError());
		return false;
	}

	mixResult = Mix_OpenAudio(
		44100,						//Frequency
		MIX_DEFAULT_FORMAT,			//Output Format
		2,							//Audio channels (1 => mono		2 => stereo)
		1024						//chunk size
	);

	if (mixResult < 0)
	{
		SDL_Log("Falied with Mix_OpenAudio: %s", Mix_GetError());
		return false;
	}

	window = SDL_CreateWindow(
		"Fighter/Platformer",		//Window Title
		100,						//Top left X
		100,						//Top left Y
		Game::winWidth,				//win Height
		Game::winHeight,			//win Width
		0							//Flags
	);

	/*
		SDL WINDOW FLAGS:		(separator: | )
			SDL_WINDOW_FULLSCREEN
			SDL_WINDOW_FULLSCREEN_DESKTOP
			SDL_WINDOW_OPENGL
			SDL_WINDOW_RESIZABLE
	*/

	if(!window)
	{
		SDL_Log("Falied to create window: %s", SDL_GetError() );
		return false;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC		//FLAGS

	);

	if (!renderer)
	{
		SDL_Log("Falied to create renderer: %s", SDL_GetError());
		return false;
	}

	goManager = new GameObjectManager();
	rendManager = new RenderManager();
	colManager = new CollisionManager();
	eventManager = new EventManager();
	inputManager = new InputManager(this);
	musicManager = new MusicManager();

	setBGcolor(0,0,0);

	Setup();

	return true;
}

void Game::RUN()
{
	while (isRunning)
	{
		INPUT();
		UPDATE();
		OUTPUT();
	}
}


void Game::SHUTDOWN()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	Log("Shutting Down game.");
}

void Game::Setup() {}

void Game::INPUT()
{
	
}


void Game::UPDATE()
{
	const int waitTime = 16;	//ms
	const double maxDeltaTime = 0.05;

	//enforce min deltaTime
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + waitTime)) {};

	double deltaTime = (SDL_GetTicks() - TicksCount) / 1000.0;
	TicksCount = SDL_GetTicks();

	//clamp max delta time
	if (deltaTime > maxDeltaTime) { deltaTime = maxDeltaTime; }

	//update Objects
	goManager->Update(deltaTime);
	inputManager->Update(deltaTime);

	//Check Collisions
	colManager->Update(deltaTime);

	//Handle Events
	eventManager->Handle(deltaTime);
}

void Game::OUTPUT()
{
	rendManager->Draw();
}

void Game::quit()
{
	isRunning = false;
	//Log("QUIT game called.");
}

void Game::addGameObject(GameObject* obj)
{
	goManager->addGameObject(obj);
}
void  Game::setBGcolor(int r, int g, int b, int a)
{
	rendManager->setBGcolor(r,g,b,a);
}
