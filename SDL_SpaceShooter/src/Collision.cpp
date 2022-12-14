#include <iostream>
#include "Collision.h"

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
	if (AABB(colliderA.GetColliderRect(), colliderB.GetColliderRect()))
	{
		//std::cout << colliderA.tag << " rect hit " << colliderB.tag << " rect" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}