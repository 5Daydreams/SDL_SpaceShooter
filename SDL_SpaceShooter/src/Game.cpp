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

std::vector<ICollider*> Game::colliders;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
float Game::deltaTime;
float currTime = 0.0f;
float lastTime = 0.0f;

ECSManager manager;

auto& player(manager.AddEntity());
auto& asteroid(manager.AddEntity());

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
	player.AddComponent<ProjectileManager>(&player.GetComponent<Transform>());
	player.AddComponent<Input>();

	asteroid.AddComponent<Transform>(300.0f, 300.0f, Vector2(1.0f, 1.0f));
	const std::string wall_texture_path = "assets/asteroid.png";
	asteroid.AddComponent<SpriteRenderer>(wall_texture_path.c_str());
	asteroid.AddComponent<Collider2D>("asteroid");
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

	ICollider& playerCollider = player.GetComponent<Collider2D>();

	for (int i = 0; i < colliders.size(); i++)
	{
		ICollider* cc1 = colliders[i];

		for (int j = i + 1; j < colliders.size(); j++)
		{
			ICollider* cc2 = colliders[j];

			bool eitherIsDisabled = !cc1->isActive || !cc2->isActive;

			if (eitherIsDisabled)
			{
				continue;
			}

			const bool collisionHappened = Collision::AABB(*cc1, *cc2);

			if (!collisionHappened)
			{
				continue;
			}

			const bool playerHitAsteroid =
				(cc1 == &playerCollider && cc2->tag == "asteroid")
				|| (cc1->tag == "asteroid" && cc2 == &playerCollider);

			if (playerHitAsteroid)
			{
				auto& playerPhys = player.GetComponent<SpaceshipMotion>();
				playerPhys.SetVelocity(playerPhys.GetVelocity() * -1);

				continue;
			}

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