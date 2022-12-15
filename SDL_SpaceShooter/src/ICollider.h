#pragma once
#include <functional>
#include <SDL_rect.h>

class ICollider
{
public:
	bool isActive;
	virtual SDL_Rect GetColliderRect() const = 0;

	ICollider()
	{

	}
};
