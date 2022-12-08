#pragma once
#include "Collider.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "../Vector2.h"


class ProjectileInstance
{
private:
	Vector2 velocity;
	Collider2D* collider;
	SpriteRenderer* renderer;
	Transform* transform;
	bool isActive;

public:

	ProjectileInstance(Collider2D* col, SpriteRenderer* rend, Transform* tran)
	{
		velocity = Vector2::Zero;
		collider = col;
		renderer = rend;
		transform = tran;
		isActive = false;
	}

	~ProjectileInstance()
	{
	}

	void FireProjectile(Vector2 spawnPos, Vector2 spawnVel)
	{
		transform->position = spawnPos;
		velocity = spawnVel;
		isActive = true;
	}

	void DisableProjectile()
	{
		isActive = false;
	}

	bool IsActive()
	{
		return isActive;
	}

	void Init()
	{
		isActive = true;
		collider->Init();
	}

	void Update()
	{
		transform->position += velocity;
	}

	void Draw()
	{
		renderer->Draw();
	}
};
