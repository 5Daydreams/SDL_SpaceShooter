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

	auto TagCheck = [colliderA, colliderB](std::string tagA, std::string tagB)
	{
		bool matching = (colliderA.tag == tagA && colliderB.tag == tagB);
		bool flipped = (colliderB.tag == tagA && colliderA.tag == tagB);

		return matching || flipped;
	};

	// This is just to ignore the player-projectile interaction. There
	if (TagCheck("projectile", "player"))
	{
		return;
	}

	if (AABB(colliderA.GetColliderRect(), colliderB.GetColliderRect()))
	{
		colliderA.TriggerCollisionCallback(colliderB);
		colliderB.TriggerCollisionCallback(colliderA);
	}
}
