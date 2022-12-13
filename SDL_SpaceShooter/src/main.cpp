#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Game.h"
#include "WindowLoop.h"

Game* game = nullptr;

int main(int argc, const char* argv[])
{
	game = new Game();
	game->Init("Cpp_Speedrun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WindowLoop::window_w, WindowLoop::window_h, false);

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