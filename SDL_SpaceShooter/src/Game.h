#pragma once

#include "SDL.h"
#include <filesystem>
#include <vector>

#include "ECS/Collider.h"
#include "ECS/ECS.h"

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
	static ECSManager ComponentManager;
	static std::vector<Collider2D*> colliders;
	static float deltaTime;

	static void PrintSDLErrorLine();

private:
	bool isRunning{};
	SDL_Window* window{};
};