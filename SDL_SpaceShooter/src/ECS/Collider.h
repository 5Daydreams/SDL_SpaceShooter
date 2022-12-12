#pragma once
#include <string>
#include "../Vector2.h"
#include "ECS.h"
#include "Transform.h"
#include "../ICollider.h"

class Collider2D : public Component, public ICollider
{
public:
	SDL_Rect colliderRect;
	Vector2 colliderScale;

	Transform* transform;

	Collider2D(std::string tag) : ICollider(tag)
	{
		colliderScale = Vector2(1.0f, 1.0f);
	}

	Collider2D(std::string tag, Vector2 scale) : ICollider(tag)
	{
		colliderScale = scale;
	}

	void Init() override
	{
		if (!entity->HasComponent<Transform>())
		{
			entity->AddComponent<Transform>();
		}

		transform = &entity->GetComponent<Transform>();

		//this->AddToColliderCache();
	}

	void Update() override
	{
		colliderRect.x = static_cast<int>(transform->position.x);
		colliderRect.y = static_cast<int>(transform->position.y);

		colliderRect.w = 64 * transform->scale.x * colliderScale.x;
		colliderRect.h = 64 * transform->scale.y * colliderScale.y;
	}

	SDL_Rect GetColliderRect() const override
	{
		return colliderRect;
	}
};
