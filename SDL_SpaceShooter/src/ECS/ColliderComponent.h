#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect colliderRect;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string tag)
	{
		this->tag = tag;
	}

	void Init()
	{
		if (!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}

		transform = &entity->GetComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void Update()
	{
		colliderRect.x = static_cast<int>(transform->position.x);
		colliderRect.y = static_cast<int>(transform->position.y);

		colliderRect.w = 64 * transform->scale.x;
		colliderRect.h = 64 * transform->scale.y;
	}
};