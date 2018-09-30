#pragma once

#include <SDL.h>

class Game
{
public:
	Game();
	~Game();

	int loop();
	void render();
	void clean();
	int initialiseSDL();

private:
	SDL_Window* mainWindow = nullptr;

	bool isRunning = true;
};

