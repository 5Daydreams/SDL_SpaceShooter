#pragma once
#include "ECS/Transform.h"

class WindowLoop
{
public:
	inline static constexpr int window_w = 800;
	inline static constexpr int window_h = 640;

	static bool CheckOutOfBounds(Vector2 pos)
	{
		if (pos.x > static_cast<float>(window_w))
		{
			return true;
		}
		else if (pos.x < 0.0f)
		{
			return true;
		}

		if (pos.y > static_cast<float>(window_h))
		{
			return true;
		}
		else if (pos.y < 0.0f)
		{
			return true;
		}

		return false;
	}

	static void LoopOnWindow(Transform* transform)
	{
		if (transform->position.x > static_cast<float>(window_w))
		{
			transform->position.x -= static_cast<float>(window_w);
		}
		else if (transform->position.x < 0.0f)
		{
			transform->position.x += static_cast<float>(window_w);
		}

		if (transform->position.y > static_cast<float>(window_h))
		{
			transform->position.y -= static_cast<float>(window_h);
		}
		else if (transform->position.y < 0.0f)
		{
			transform->position.y += static_cast<float>(window_h);
		}
	}

	static Vector2& LoopOnWindow(Vector2& position)
	{
		if (position.x > static_cast<float>(window_w))
		{
			position.x -= static_cast<float>(window_w);
		}
		else if (position.x < 0.0f)
		{
			position.x += static_cast<float>(window_w);
		}

		if (position.y > static_cast<float>(window_h))
		{
			position.y -= static_cast<float>(window_h);
		}
		else if (position.y < 0.0f)
		{
			position.y += static_cast<float>(window_h);
		}

		return position;
	}
};
