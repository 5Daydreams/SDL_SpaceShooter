#pragma once

#include "ECS.h"
#include "Components.h"

class ControllerComponent : public Component
{
public:
	TransformComponent* transform;

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{

		// Refactor: try to setup a key DOWN,HELD,RELEASED system
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0.0f;
				break;
			case SDLK_s:
				transform->velocity.y = 0.0f;
				break;
			case SDLK_a:
				transform->velocity.x = 0.0f;
				break;
			case SDLK_d:
				transform->velocity.x = 0.0f;
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1.0f;
				break;
			case SDLK_s:
				transform->velocity.y = 1.0f;
				break;
			case SDLK_a:
				transform->velocity.x = -1.0f;
				break;
			case SDLK_d:
				transform->velocity.x = 1.0f;
				break;
			default:
				break;
			}
		}
	}


};