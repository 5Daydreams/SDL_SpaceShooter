#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/Transform.h"
#include "ECS/SpriteRenderer.h"
#include "ECS/Collider.h"
#include "ECS/Input.h"
#include "ECS/SpaceshipMotion.h"
#include "ECS/ProjectileManager.h"
#include "ICollider.h"

#include "Vector2.h"
#include "Collision.h"
#include "ECS/Asteroid.h"
#include "Random.h"

std::vector<Collider2D*> Game::colliders;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

float Game::deltaTime;
float currTime = 0.0f;
float lastTime = 0.0f;

ECSManager Game::ComponentManager;

Entity& player(Game::ComponentManager.AddEntity());
//Entity& asteroid(Game::ComponentManager.AddEntity());

void Game::PrintSDLErrorLine()
{
	std::cout << SDL_GetError() << std::endl;
}

Game::Game() {}

Game::~Game() {}

bool Game::IsRunning() const
{
	return isRunning;
};

void SpawnAsteroid(Vector2 position)
{
	Entity& newAsteroid(Game::ComponentManager.AddEntity());

	newAsteroid.AddComponent<Transform>(position, Vector2(1.0f, 1.0f));

	const std::string asteroid_texture_path = "assets/asteroid.png";
	newAsteroid.AddComponent<SpriteRenderer>(asteroid_texture_path.c_str());

	newAsteroid.AddComponent<Collider2D>("asteroid");
	newAsteroid.GetComponent<Collider2D>().isActive = true;

	newAsteroid.AddComponent<Asteroid>();
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

	Random::Init();

	player.AddComponent<Transform>(50.0f, 50.0f, Vector2(1.0f, 1.0f));
	const std::string spaceship_texture_path = "assets/spaceship.png";
	player.AddComponent<SpriteRenderer>(spaceship_texture_path.c_str());
	player.AddComponent<SpaceshipMotion>();
	player.AddComponent<Collider2D>("player");
	player.GetComponent<Collider2D>().isActive = true;
	player.AddComponent<ProjectileManager>();
	player.AddComponent<Input>();

	SpawnAsteroid(Vector2(300.0f, 300.0f));
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_p)
		{
			// printf("The 'P' key is pressed.\n");
			Vector2 center = {
				WindowLoop::window_w / 2.0f,
				WindowLoop::window_h / 2.0f
			};

			SpawnAsteroid(center);
		}
		break;

	default:
		break;
	}
}

void Game::Update()
{
	currTime = SDL_GetTicks() / 1000.0f;
	Game::deltaTime = (currTime - lastTime);

	ComponentManager.Refresh();
	ComponentManager.Update();

	for (int i = 0; i < colliders.size(); i++)
	{
		Collider2D* cc1 = colliders[i];

		for (int j = i + 1; j < colliders.size(); j++)
		{
			Collider2D* cc2 = colliders[j];

			const bool collisionHappened = Collision::AABB(*cc1, *cc2);

			if (!collisionHappened)
			{
				continue;
			}


		}
	}

	lastTime = currTime;
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	ComponentManager.Draw();

	SDL_RenderPresent(renderer);
}

void Game::Clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Quitting application." << std::endl;
}