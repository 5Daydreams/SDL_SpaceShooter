#pragma once
#include <vector>
#include "../Vector2.h"
#include "ECS.h"
#include "ProjectileInstance.h"


const int PROJECTILE_POOL_COUNT = 100;

class ProjectileManager : public Component
{
	std::vector<ProjectileInstance> projectiles;

public:

	ProjectileManager()
	{
		projectiles = std::vector<ProjectileInstance>{};
		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++) {

			ProjectileInstance temp = ProjectileInstance();
			(
				velocity = ;
			collider = ;
			renderer = ;
			transform = ;
			isActive = ;
			);

			projectiles.push_back();
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
			if (!projectiles[i].IsActive()) {
				index = i;
				break;
			}
		}

		// Failed to find inactive pool element - do not spawn a new projectile
		if (index == -1) {
			return;
		}

		projectiles[index].FireProjectile(spawnPos, spawnVel);
	}

	void DisableProjectile(int index)
	{
		projectiles[index].DisableProjectile();
	}

	//void ForAllProjectiles(std::function<void(ProjectileInstance&)> f)
	//{
	//	for (int i = 0; i < projectiles.size(); i++)
	//	{
	//		if (projectiles[i].IsActive())
	//		{
	//			f(projectiles[i]);
	//		}
	//	}
	//}


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

/*
 In an ECS architecture, the most memory-friendly approach for a projectile system would likely be to use
 a single component to represent all projectiles in the game,
 rather than having a separate component for each individual projectile.

In ECS, entities are typically represented as just a unique identifier,
and the data and behavior of the entity are stored in components.
A common approach to implementing a projectile system in ECS is to have a separate component for each projectile,
with each component containing the data for that specific projectile, such as its position, velocity, and color.

However, this approach can quickly become memory-intensive, especially in games with a large number of projectiles.
An alternative approach that can be more memory-friendly is to use a single component to represent all projectiles in the game,
and to store the data for each projectile in an array within that component.

For example, you could have a ProjectileComponent that contains an array of positions, velocities, and colors for each projectile.
The ProjectileComponent would also contain a separate array of flags to indicate which projectiles are currently active in the game.
This approach allows you to store all of the data for the projectiles in a single component,
which can be more memory-efficient than having a separate component for each projectile.

Additionally, you can use a system to iterate over the array of projectiles in the ProjectileComponent and
update the position of each projectile based on its velocity.
This allows you to easily and efficiently update the position of all projectiles in the game
without having to iterate over a large number of separate components.

Overall, using a single component to represent all projectiles in the game can be a more memory-friendly approach to implementing a projectile system in ECS.
It allows you to store the data for all projectiles in a single component, and to efficiently update the position of all projectiles using a system.
*/