#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class Collider2D : public Component
{
public:
	SDL_Rect colliderRect;
	Vector2 colliderScale;
	std::string tag;

	Transform* transform;

	Collider2D(std::string tag)
	{
		colliderScale = Vector2(1.0f, 1.0f);
		this->tag = tag;
	}

	Collider2D(std::string tag, Vector2 scale)
	{
		colliderScale = scale;
		this->tag = tag;
	}

	void Init()
	{
		if (!entity->HasComponent<Transform>())
		{
			entity->AddComponent<Transform>();
		}

		transform = &entity->GetComponent<Transform>();

		Game::colliders.push_back(this);
	}

	void Update()
	{
		colliderRect.x = static_cast<int>(transform->position.x);
		colliderRect.y = static_cast<int>(transform->position.y);

		colliderRect.w = 64 * transform->scale.x * colliderScale.x;
		colliderRect.h = 64 * transform->scale.y * colliderScale.y;
	}
};