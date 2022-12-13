#pragma once
#include <functional>
#include <SDL_rect.h>
#include "Game.h"

class ICollider
{
public:
	bool isActive;
	std::string tag;
	virtual SDL_Rect GetColliderRect() const = 0;
	std::vector<std::function<void()>> onCollision = std::vector<std::function<void()>>{};

	ICollider(std::string objTag)
	{
		tag = objTag;
		//Game::colliders.push_back(this);
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
