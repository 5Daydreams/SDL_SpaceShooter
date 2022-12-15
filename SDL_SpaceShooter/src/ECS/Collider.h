#pragma once
#include <functional>
#include <string>
#include "../Vector2.h"
#include "ECS.h"
#include "Transform.h"
#include "../Game.h"

class Collider2D : public Component
{
public:
	std::string tag;
	bool isActive;

	SDL_Rect colliderRect;
	Vector2 colliderScale;

	std::vector<std::function<void(const Collider2D&)>> onCollision = std::vector<std::function<void(const Collider2D&)>>{};
	Transform* transform;

	Collider2D(std::string colliderTag) : tag(colliderTag)
	{
		colliderScale = Vector2(1.0f, 1.0f);

		Game::colliders.push_back(this);
	}

	Collider2D(std::string colliderTag, Vector2 scale) : tag(colliderTag)
	{
		colliderScale = scale;

		Game::colliders.push_back(this);
	}

	void Init() override
	{
		if (!entity->HasComponent<Transform>())
		{
			entity->AddComponent<Transform>();
		}

		transform = &entity->GetComponent<Transform>();
	}

	void Update() override
	{
		colliderRect.x = static_cast<int>(transform->position.x);
		colliderRect.y = static_cast<int>(transform->position.y);

		colliderRect.w = 64 * transform->scale.x * colliderScale.x;
		colliderRect.h = 64 * transform->scale.y * colliderScale.y;
	}

	SDL_Rect GetColliderRect() const
	{
		return colliderRect;
	}

	void SubscribeToCollisionCallback(const std::function<void(const Collider2D& other)>& callback)
	{
		onCollision.push_back(callback);
	}

	void TriggerCollisionCallback(const Collider2D& other) const
	{
		for (const auto& callback : onCollision)
		{
			callback(other);
		}
	}
};
