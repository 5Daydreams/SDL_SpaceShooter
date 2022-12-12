#pragma once
#include "SDL.h"
#include "ECS/Collider.h"

class ICollider;

class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ICollider& colliderA, const ICollider& colliderB);

};