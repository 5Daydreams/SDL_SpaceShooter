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

void Collision::TryAABB(const Collider2D& colliderA, const Collider2D& colliderB)
{
	if (bool eitherIsDisabled = (!colliderA.isActive) || (!colliderB.isActive))
	{
		return;
	}

	if (AABB(colliderA.GetColliderRect(), colliderB.GetColliderRect()))
	{
		colliderA.TriggerCollisionCallback(colliderB);
		colliderB.TriggerCollisionCallback(colliderA);
	}
}