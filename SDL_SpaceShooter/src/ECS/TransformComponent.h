#pragma once
#include "Components.h"
#include "Vector2.h"

class TransformComponent : public Component
{
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 scale;

	float speed = 2.2f;

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
		scale.x = 1.0f;
		scale.y = 1.0f;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(Vector2 pos)
	{
		position = pos;
	}

	TransformComponent(float x, float y, Vector2 scale)
	{
		this->position.x = x;
		this->position.y = y;
		this->scale = scale;
	}

	TransformComponent(float xPos, float yPos, float xScale, float yScale)
	{
		this->position.x = xPos;
		this->position.y = yPos;
		this->scale.x = xScale;
		this->scale.y = yScale;
	}

	TransformComponent(Vector2 pos, Vector2 scale)
	{
		this->position = pos;
		this->scale = scale;
	}

	void Init() override
	{
		velocity = Vector2(0.0f, 0.0f);
	}

	void Update() override
	{
		position += velocity * speed;
		//std::cout << "pos: " << position << "; vel: " << velocity << std::endl;
	}
};