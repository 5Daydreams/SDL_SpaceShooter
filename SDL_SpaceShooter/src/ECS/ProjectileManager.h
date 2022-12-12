#pragma once
#include <vector>
#include "../Vector2.h"
#include "ECS.h"
#include "../Game.h"
#include "Projectiles/ProjectileInstance.h"


const int PROJECTILE_POOL_COUNT = 100;

class ProjectileManager : public Component
{
private:
	std::vector<ProjectileInstance*> projectiles;
	const Vector2 offset = Vector2(0, -16);
	const Vector2 baseOffset = Vector2(16, 16);
	const Transform* transform;

public:

	ProjectileManager()
	{
		projectiles = std::vector<ProjectileInstance*>();

		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++)
		{
			Entity& temp(Game::ComponentManager.AddEntity());

			temp.AddComponent<Transform>();
			temp.AddComponent<SpriteRenderer>("assets/projectile.png");
			temp.AddComponent<Collider2D>("projectile");
			ProjectileInstance& proj = temp.AddComponent<ProjectileInstance>();

			projectiles.push_back(&proj);
			proj.DisableProjectile();
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
			if (!projectiles[i]->IsActive())
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
		projectiles[index]->FireProjectile(spawnPos + baseOffset + offsetRotated, spawnVel * -1.0f);
	}

	void DisableProjectile(int index)
	{
		projectiles[index]->DisableProjectile();
	}


	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
	}

	void Update() override
	{

	}

	void Draw() override
	{

	}
};