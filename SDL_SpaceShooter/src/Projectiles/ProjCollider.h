#pragma once
#include <string>
#include "../Game.h"
#include "../Vector2.h"
#include "ProjTransform.h"
#include "../ICollider.h"


class ProjCollider2D
{
public:
	SDL_Rect colliderRect;
	Vector2 colliderScale;

	ProjTransform* transform;

	ProjCollider2D(ProjTransform* pTran, std::string tag)
	{
		transform = pTran;
		colliderScale = Vector2(1.0f, 1.0f);
	}

	void Update()
	{
		colliderRect.x = static_cast<int>(transform->position.x);
		colliderRect.y = static_cast<int>(transform->position.y);

		colliderRect.w = 64 * transform->scale.x * colliderScale.x;
		colliderRect.h = 64 * transform->scale.y * colliderScale.y;
	}

	//SDL_Rect GetColliderRect() const override
	//{
	//	return colliderRect;
	//}
};
