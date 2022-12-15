#pragma once
#include "../Vector2.h"
#include "../ECS/Transform.h"
#include "../ECS/Collider.h"
#include "../ECS/SpriteRenderer.h"
#include "../WindowLoop.h"


class ProjectileInstance : public Component
{
public:
	void DisableProjectile()
	{
		isActive = false;
		collider->isActive = false;
		renderer->isActive = false;
	}

private:
	Vector2 velocity;
	Collider2D* collider;
	SpriteRenderer* renderer;
	Transform* transform;
	bool isActive;
	const float projectileSpeed = 17.0f;

	const std::function<void(const Collider2D&)> collisionCallback = [this](const Collider2D& other)
	{
		if (other.tag == "asteroid")
		{
			DisableProjectile();
		}
	};

public:

	~ProjectileInstance() {}

	bool IsActive()
	{
		return isActive;
	}

	void EnableProjectile()
	{
		isActive = true;
		collider->isActive = true;
		renderer->isActive = true;
	}
	
	void Init() override
	{
		velocity = Vector2::Zero;
		transform = &entity->GetComponent<Transform>();
		collider = &entity->GetComponent<Collider2D>();
		renderer = &entity->GetComponent<SpriteRenderer>();
		isActive = false;

		collider->SubscribeToCollisionCallback(collisionCallback);
	}

	void FireProjectile(Vector2 spawnPos, Vector2 spawnVel)
	{
		transform->position = spawnPos;
		velocity = spawnVel * projectileSpeed;
		EnableProjectile();
	}

	void MovementLogic()
	{
		transform->position += velocity;

		if (WindowLoop::CheckOutOfBounds(transform->position))
		{
			this->DisableProjectile();
		}
	}

	void Update() override
	{
		if (!isActive)
		{
			return;
		}

		MovementLogic();
	}

	void Draw() override
	{
		renderer->Draw();
	}
};
