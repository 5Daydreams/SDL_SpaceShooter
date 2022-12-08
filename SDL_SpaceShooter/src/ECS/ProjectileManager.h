#pragma once
#include <vector>
#include "SDL.h"
#include "Components.h"


const int PROJECTILE_POOL_COUNT = 1000;

class ProjectileManager : public Component
{

	std::vector<ProjectileInstance> projectiles;

public:

	ProjectileManager() : projectiles(PROJECTILE_POOL_COUNT)
	{
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

		if (index == -1) {
			return;
		}

		projectiles[index].FireProjectile(spawnPos, spawnVel);
	}

	void Init()
	{

	}

	void Update()
	{

	}
};

// Define the ProjectileComponent class
class ProjectileComponent {
public:
	// Constructor to initialize the array of projectiles and flags
	ProjectileComponent() : projectiles(PROJECTILE_POOL_COUNT), flags(PROJECTILE_POOL_COUNT) {}

	// Function to add a new projectile to the game
	void addProjectile(int x, int y, int dx, int dy, int width, int height, SDL_Color color) {
		// Find the first inactive projectile in the array
		int index = -1;
		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++) {
			if (!flags[i]) {
				index = i;
				break;
			}
		}

		// If there are no inactive projectiles, return
		if (index == -1) {
			return;
		}

		// Create a new projectile with the specified attributes and add it to the array
		projectiles[index] = Projectile(x, y, dx, dy, width, height, color);

		// Set the flag for the projectile to indicate that it is active
		flags[index] = true;
	}

	// Function to remove a projectile from the game
	void removeProjectile(int index) {
		// Set the flag for the projectile to indicate that it is inactive
		flags[index] = false;
	}

	// Function to iterate over the active projectiles in the array
	void forEachActive(std::function<void(Projectile&)> f) {
		for (int i = 0; i < PROJECTILE_POOL_COUNT; i++) {
			if (flags[i]) {
				f(projectiles[i]);
			}
		}
	}

private:
	// Array of projectiles
	std::vector<Projectile> projectiles;

	// Array of flags to indicate which projectiles are active
	std::vector<bool> flags;
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