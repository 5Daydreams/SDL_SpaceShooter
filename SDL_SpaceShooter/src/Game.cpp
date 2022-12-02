#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;


auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

auto& tile0(manager.AddEntity());
auto& tile1(manager.AddEntity());
auto& tile2(manager.AddEntity());

void Game::PrintSDLErrorLine()
{
	std::cout << SDL_GetError() << std::endl;
}


void Game::Init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Subsystems Initialized succesfully." << std::endl;

		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
		if (window)
		{
			std::cout << "Window created." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 30, 80, 210, 255);
			std::cout << "Renderer created." << std::endl;
		}

		isRunning = true;
	}
	else
	{
		std::cout << "SDL_Init() failed." << std::endl;
		isRunning = false;
	}


	map = new Map();

	tile0.AddComponent<TileComponent>(200, 200, 64, 64, 0);
	tile1.AddComponent<TileComponent>(250, 250, 64, 64, 1);
	tile1.AddComponent<ColliderComponent>("grass");
	tile2.AddComponent<TileComponent>(150, 150, 64, 64, 2);
	tile2.AddComponent<ColliderComponent>("dirt");

	player.AddComponent<TransformComponent>(0.0f, 0.0f, Vector2(1.0f, 1.0f));
	const std::string stickman_texture_path = "assets/stickman.png";
	player.AddComponent<SpriteComponent>(stickman_texture_path.c_str());
	player.AddComponent<ControllerComponent>();
	player.AddComponent<ColliderComponent>("player");

	wall.AddComponent<TransformComponent>(300.0f, 300.0f, Vector2(1.0f, 1.0f));
	const std::string wall_texture_path = "assets/dirt.png";
	wall.AddComponent<SpriteComponent>(wall_texture_path.c_str());
	wall.AddComponent<ColliderComponent>("wall");
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	//if (Collision::AABB(player.GetComponent<ColliderComponent>().colliderRect, wall.GetComponent<ColliderComponent>().colliderRect))
	//{
	//	player.GetComponent<TransformComponent>().velocity *= -1;
	//	std::cout << "Wall Hit!" << std::endl;
	//}

	ColliderComponent& playerCollider = player.GetComponent<ColliderComponent>();

	for (ColliderComponent* cc : colliders)
	{
		if (cc == &playerCollider)
		{
			continue;
		}

		if (Collision::AABB(playerCollider, *cc))
		{
			player.GetComponent<TransformComponent>().velocity *= -1;
		}
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	//map->DrawMap();
	manager.Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Quitting application." << std::endl;
}

bool Game::IsRunning() const { return isRunning; };