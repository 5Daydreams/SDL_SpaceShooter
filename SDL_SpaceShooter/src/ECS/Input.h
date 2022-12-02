#pragma once

#include "ECS.h"
#include "Components.h"

class KeyCallbacks
{
private:
	SDL_KeyCode key;
	bool currentlyHeld = false;

public:

	void UpdateKeyState()
	{
		bool keyMatches = Game::event.key.keysym.sym == key;

		if (!keyMatches)
		{
			return;
		}

		bool oldState = currentlyHeld;

		switch (Game::event.type)
		{
		case SDL_KEYDOWN:
			currentlyHeld = true;
			break;
		case SDL_KEYUP:
			currentlyHeld = false;
			break;
		default:
			// KeyState doesn't change if it isn't up or down
			break;
		}

		if (oldState != currentlyHeld)
		{
			if (currentlyHeld)
			{
				// OnKeyPressed();
			}
			else
			{
				// OnKeyReleased();
			}
		}
		else // oldState == currentHeldState
		{
			if (currentlyHeld)
			{
				// OnKeyHeld();
			}
		}

	}

};

class Input : public Component
{
public:
	Transform* transform;

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
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