#include "Collision.h"
#include "ECS/Collider.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	bool collisionWasDetected = (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		);

	return collisionWasDetected;
}

bool Collision::AABB(const Collider2D& colliderA, const Collider2D& colliderB)
{
	if (AABB(colliderA.colliderRect, colliderB.colliderRect))
	{
		std::cout << colliderA.tag << " hit: " << colliderB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}