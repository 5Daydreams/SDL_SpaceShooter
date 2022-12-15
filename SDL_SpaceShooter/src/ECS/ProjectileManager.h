#pragma once
#include <vector>
#include "../Vector2.h"
#include "ECS.h"
#include "../Game.h"
#include "ProjectileInstance.h"


const int PROJECTILE_POOL_COUNT = 20;

class ProjectileManager : public Component
{
private:
	std::vector<ProjectileInstance*> projectiles;
	const Vector2 offset = Vector2(0, -32);
	const Vector2 baseOffset = Vector2(32, 32);
	const Transform* transform;

public:

	ProjectileManager()
	{
		projectiles = std::vector<ProjectileInstance*>();

		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++)
		{
			Entity& temp(Game::ComponentManager.AddEntity());

			temp.AddComponent<Transform>().scale = Vector2(0.15f, 0.15f);
			temp.AddComponent<SpriteRenderer>("assets/projectile.png");
			temp.AddComponent<Collider2D>("projectile");
			ProjectileInstance& proj = temp.AddComponent<ProjectileInstance>();

			projectiles.push_back(&proj);
			proj.DisableProjectile();
		}
	}

	~ProjectileManager() {}

	void SpawnProjectile(Vector2 spawnPos, Vector2 spawnVel)
	{
		// Search for inactive references within the pool
		int index = -1;
		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++)
		{
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

		const Vector2 offsetFixed = baseOffset + offset.Rotate(transform->rotation);

		projectiles[index]->FireProjectile(spawnPos + offsetFixed, spawnVel * -1.0f);
		// Note.: I can't find where the error is, but the *(-1) is required to align the projectile velocity to the actual firing direction
	}

	void DisableProjectile(int index)
	{
		projectiles[index]->DisableProjectile();
	}


	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
	}

	void Update() override {}

	void Draw() override {}
};