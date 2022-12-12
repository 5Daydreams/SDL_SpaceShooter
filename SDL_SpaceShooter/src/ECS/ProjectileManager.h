#pragma once
#include <vector>
#include "../Vector2.h"
#include "ECS.h"
#include "Projectiles/ProjectileInstance.h"
#include "Projectiles/ProjCollider.h"


const int PROJECTILE_POOL_COUNT = 100;

class ProjectileManager : public Component
{
private:
	std::vector<ProjectileInstance> projectiles;
	const Vector2 offset = Vector2(0,-16);
	const Vector2 baseOffset = Vector2(16,16);
	const Transform* transform;

public:

	ProjectileManager(Transform* transform) : transform(transform)
	{
		projectiles = std::vector<ProjectileInstance>();
		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++) {

			ProjTransform* proj_transform = new ProjTransform(Vector2::Zero, Vector2::One);
			ProjCollider2D* collider = new ProjCollider2D(proj_transform, "projectile");
			ProjectileRenderer* renderer = new ProjectileRenderer(proj_transform, "assets/projectile.png");

			ProjectileInstance temp = ProjectileInstance(collider, renderer, proj_transform);

			projectiles.push_back(temp);
		}
	}

	~ProjectileManager()
	{
	}

	void SpawnProjectile(Vector2 spawnPos, Vector2 spawnVel)
	{
		// Search for inactive references within the pool
		int index = -1;
		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++) {
			if (!projectiles[i].IsActive()) 
			{
				index = i;
				break;
			}
		}

		// Failed to find inactive pool element - do not spawn a new projectile
		if (index == -1) 
		{
			return;
		}

		const Vector2 offsetScaled = Vector2
		(
			offset.x * transform->scale.x,
			offset.y * transform->scale.y
		);

		const Vector2 offsetRotated = offsetScaled.Rotate(transform->rotation);

		// Note.: I can't find where the error is, but the *(-1) is required to align the projectile velocity to the actual firing direction
		projectiles[index].FireProjectile(spawnPos + baseOffset + offsetRotated, spawnVel * -1);
	}

	void DisableProjectile(int index)
	{
		projectiles[index].DisableProjectile();
	}


	void Init() override
	{
		for (int i = 0; i < projectiles.size(); i++) {
			if (projectiles[i].IsActive())
			{
				projectiles[i].DisableProjectile();
			}
		}
	}

	void Update() override
	{
		for (int i = 0; i < projectiles.size(); i++) {
			if (projectiles[i].IsActive())
			{
				projectiles[i].Update();
			}
		}
	}

	void Draw() override
	{
		for (int i = 0; i < projectiles.size(); i++)
		{
			if (projectiles[i].IsActive())
			{
				projectiles[i].Draw();
			}
		}
	}
};