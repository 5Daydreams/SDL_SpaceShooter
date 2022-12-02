#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <filesystem>
#include <iostream>
#include <vector>

class Collider2D;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean() const;

	bool IsRunning() const;

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<Collider2D*> colliders;
	static void PrintSDLErrorLine();

private:

	bool isRunning{};
	SDL_Window* window{};
};