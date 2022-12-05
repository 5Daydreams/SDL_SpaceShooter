#pragma once

#include "Components.h"
#include <functional>
#include <map>


class KeyCallback
{
private:
	const SDL_KeyCode key;

public:
	std::vector<std::function<void()>> onKeyDown = std::vector<std::function<void()>>{};
	std::vector<std::function<void()>> onKeyHeld = std::vector<std::function<void()>>{};
	std::vector<std::function<void()>> onKeyUp = std::vector<std::function<void()>>{};
	bool currentlyHeld = false;

	KeyCallback()
		:key(SDL_KeyCode::SDLK_SPACE)
	{
	}

	KeyCallback(const SDL_KeyCode key) : key(key)
	{
	}

	~KeyCallback() {}

	SDL_KeyCode GetKeyCode() const
	{
		return key;
	}

	void SubscribeToKeyDown(std::function<void()> callback)
	{
		onKeyDown.push_back(callback);
	}

	void SubscribeToKeyHeld(std::function<void()> callback)
	{
		onKeyHeld.push_back(callback);
	}

	void SubscribeToKeyUp(std::function<void()> callback)
	{
		onKeyUp.push_back(callback);
	}

	void TriggerOnKeyDown() const
	{
		for (auto callback : onKeyDown)
		{
			callback();
		}
	}

	void TriggerOnKeyHeld() const
	{
		for (auto callback : onKeyHeld)
		{
			callback();
		}
	}

	void TriggerOnKeyUp() const
	{
		for (auto callback : onKeyUp)
		{
			callback();
		}
	}
};

class Input : public Component
{
private:
	Transform* transform;
	PhysicsMotion* phys;

public:
	Vector2 axisInput = Vector2::Zero;
	std::map<char, KeyCallback> inputResponses;

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
		phys = &entity->GetComponent<PhysicsMotion>();

		inputResponses.insert(std::pair<char, KeyCallback>('w', KeyCallback(SDLK_w)));
		inputResponses.insert(std::pair<char, KeyCallback>('s', KeyCallback(SDLK_s)));
		inputResponses.insert(std::pair<char, KeyCallback>('a', KeyCallback(SDLK_a)));
		inputResponses.insert(std::pair<char, KeyCallback>('d', KeyCallback(SDLK_d)));
		inputResponses.insert(std::pair<char, KeyCallback>(' ', KeyCallback(SDLK_SPACE)));

		// Add the callbacks

		// void SubscribeToKeyHeld(std::function<void()> callback);

		auto w = [this]() {this->axisInput.y = -1.0f; };
		auto s = [this]() {this->axisInput.y = 1.0f; };
		auto verticalZero = [this]() {this->axisInput.y = 0.0f; };
		auto space = [this]() {std::cout << "Pressed space" << std::endl; };

		auto a = [this]() {this->axisInput.x = -1.0f; };
		auto d = [this]() {this->axisInput.x = 1.0f; };
		auto horizontalZero = [this]() {this->axisInput.x = 0.0f; };

		inputResponses['w'].SubscribeToKeyHeld(w);
		inputResponses['s'].SubscribeToKeyHeld(s);
		inputResponses['w'].SubscribeToKeyUp(verticalZero);
		inputResponses['s'].SubscribeToKeyUp(verticalZero);
		inputResponses[' '].SubscribeToKeyHeld(space);

		inputResponses['a'].SubscribeToKeyHeld(a);
		inputResponses['d'].SubscribeToKeyHeld(d);
		inputResponses['a'].SubscribeToKeyUp(horizontalZero);
		inputResponses['d'].SubscribeToKeyUp(horizontalZero);
	}

	void Update() override
	{
		const SDL_Keycode keyCode = Game::event.key.keysym.sym;

		if (keyCode == 0)
		{
			return;
		}

		for (auto& [_, inputEvent] : inputResponses)
		{
			// KeyState doesn't change if it isn't up or down
			if (inputEvent.currentlyHeld)
			{
				inputEvent.TriggerOnKeyHeld();
			}

			bool keyMatches = keyCode == inputEvent.GetKeyCode();

			if (!keyMatches)
			{
				inputEvent.TriggerOnKeyDown();
				continue;
			}

			switch (Game::event.type)
			{
			case SDL_KEYUP:
				inputEvent.currentlyHeld = false;
				inputEvent.TriggerOnKeyUp();
				break;
			case SDL_KEYDOWN:
				inputEvent.currentlyHeld = true;
				inputEvent.TriggerOnKeyDown();
				break;
			default:
				break;
			}
		}

		axisInput.Normalize();
		phys->AddForce(axisInput.y * Vector2::Forward);
		phys->AddTorque(-axisInput.x);
		axisInput = Vector2::Zero;
	}
};