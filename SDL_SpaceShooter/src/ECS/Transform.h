#pragma once
#include "Components.h"
#include "Vector2.h"

class Transform : public Component
{
public:
	Vector2 position;
	float rotation = 0.0f;
	Vector2 scale;

	Vector2 velocity;
	float speed = 3.0f;

	Vector2 forward = Vector2(cos(rotation), sin(rotation));
	Vector2 right = Vector2(cos(rotation), sin(rotation));

	Transform()
	{
		position.x = 0.0f;
		position.y = 0.0f;
		scale.x = 1.0f;
		scale.y = 1.0f;
	}

	Transform(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	Transform(Vector2 pos)
	{
		position = pos;
	}

	Transform(float x, float y, Vector2 scale)
	{
		this->position.x = x;
		this->position.y = y;
		this->scale = scale;
	}

	Transform(float xPos, float yPos, float xScale, float yScale)
	{
		this->position.x = xPos;
		this->position.y = yPos;
		this->scale.x = xScale;
		this->scale.y = yScale;
	}

	Transform(Vector2 pos, Vector2 scale)
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


		rotation += 1;
		position += velocity * speed;
		//std::cout << "pos: " << position << "; vel: " << velocity << std::endl;
	}
};