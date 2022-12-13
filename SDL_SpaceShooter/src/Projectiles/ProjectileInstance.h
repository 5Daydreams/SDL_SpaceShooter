#pragma once
#include "../Vector2.h"
#include "../ECS/Transform.h"
#include "../ECS/Collider.h"
#include "../ECS/SpriteRenderer.h"
#include "../WindowLoop.h"


class ProjectileInstance : public Component
{
private:
	Vector2 velocity;
	Collider2D* collider;
	SpriteRenderer* renderer;
	Transform* transform;
	bool isActive;
	const float projectileSpeed = 3.0f;

public:

	void Init() override
	{
		velocity = Vector2::Zero;
		transform = &entity->GetComponent<Transform>();
		collider = &entity->GetComponent<Collider2D>();
		renderer = &entity->GetComponent<SpriteRenderer>();
		isActive = false;
	}

	~ProjectileInstance()
	{
	}

	void FireProjectile(Vector2 spawnPos, Vector2 spawnVel)
	{
		transform->position = spawnPos;
		velocity = spawnVel * projectileSpeed;
		EnableProjectile();
	}

	void EnableProjectile()
	{
		isActive = true;
		collider->isActive = true;
		renderer->isActive = true;
	}

	void DisableProjectile()
	{
		isActive = false;
		collider->isActive = false;
		renderer->isActive = false;
	}

	bool IsActive()
	{
		return isActive;
	}

	void Update() override
	{
		if (!isActive)
		{
			return;
		}

		transform->position += velocity;

		if (WindowLoop::CheckOutOfBounds(transform->position))
		{
			this->DisableProjectile();
		}
	}

	void Draw() override
	{
		renderer->Draw();
	}
};
