#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

static constexpr unsigned int WINDOW_W = 800;
static constexpr unsigned int WINDOW_H = 640;


int main(int argc, const char* argv[])
{
	game = new Game();
	game->Init("Cpp_Speedrun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, false);

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 currTime;
	int frameDeltaTime;

	while (game->IsRunning())
	{
		currTime = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameDeltaTime = SDL_GetTicks() - currTime;

		if (frameDelay > frameDeltaTime)
		{
			SDL_Delay(frameDelay - frameDeltaTime);
		}
	}
	game->Clean();

	return 0;
}