#include "Game.h"
#include "ECS/Components.h"
#include "Vector2.h"
#include "Collision.h"

std::vector<Collider2D*> Game::colliders;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
float Game::deltaTime;
float currTime = 0.0f;
float lastTime = 0.0f;

ECSManager manager;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

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


	player.AddComponent<Transform>(50.0f, 50.0f, Vector2(1.0f, 1.0f));
	const std::string stickman_texture_path = "assets/spaceship.png";
	player.AddComponent<SpriteRenderer>(stickman_texture_path.c_str());
	player.AddComponent<SpaceshipMotion>();
	player.AddComponent<Collider2D>("player");
	player.AddComponent<Input>();

	wall.AddComponent<Transform>(300.0f, 300.0f, Vector2(1.0f, 1.0f));
	const std::string wall_texture_path = "assets/asteroid.png";
	wall.AddComponent<SpriteRenderer>(wall_texture_path.c_str());
	wall.AddComponent<Collider2D>("wall");
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
	currTime = SDL_GetTicks() / 1000.0f;
	Game::deltaTime = (currTime - lastTime);

	manager.Refresh();
	manager.Update();

	Collider2D& playerCollider = player.GetComponent<Collider2D>();

	for (Collider2D* cc : colliders)
	{
		if (cc == &playerCollider)
		{
			continue;
		}

		if (Collision::AABB(playerCollider, *cc))
		{
			auto& phys = player.GetComponent<SpaceshipMotion>();
			phys.SetVelocity(phys.GetVelocity() * -1);
		}
	}

	lastTime = currTime;
}

void Game::Render()
{
	SDL_RenderClear(renderer);

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