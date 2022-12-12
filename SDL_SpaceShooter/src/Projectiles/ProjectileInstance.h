#pragma once
#include "ProjCollider.h"
#include "ProjTransform.h"
#include "ProjectileRenderer.h"
#include "../Vector2.h"


class ProjectileInstance
{
private:
	Vector2 velocity;
	ProjCollider2D* collider;
	ProjectileRenderer* renderer;
	ProjTransform* transform;
	bool isActive;

public:

	ProjectileInstance(ProjCollider2D* col, ProjectileRenderer* rend, ProjTransform* tran)
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
		collider->isActive = false;
	}

	bool IsActive()
	{
		return isActive;
	}

	void Update()
	{
		transform->position += velocity;
		renderer->Update();
		collider->Update();
	}

	void Draw()
	{
		renderer->Draw();
	}
};
