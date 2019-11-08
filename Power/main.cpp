#include "Power.h"
#include  "Game.h"

using namespace std;

int main(int argc, char** args)
{
	Game* game = new Game();

	if (game->INITIALIZE())
	{
		game->RUN();
	}
	game->SHUTDOWN();
	
	return 0;
}