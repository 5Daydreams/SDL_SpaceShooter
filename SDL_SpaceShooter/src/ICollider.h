#pragma once
#include <functional>
#include <SDL_rect.h>

class ICollider
{
public:
	bool isActive;
	virtual SDL_Rect GetColliderRect() const = 0;
	std::vector<std::function<void()>> onCollision = std::vector<std::function<void()>>{};

	ICollider()
	{

	}

	void SubscribeToCollisionCallback(std::function<void()> callback)
	{
		onCollision.push_back(callback);
	}

	void TriggerCollisionCallback() const
	{
		for (auto callback : onCollision)
		{
			callback();
		}
	}
};
