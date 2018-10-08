#include "stdafx.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	Game * pGame = new Game();

	pGame->initialise();
	pGame->getVertex();
	pGame->getShaders();
	pGame->loop();

	return 0;
}