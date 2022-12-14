#pragma once
#include "ECS.h"
#include "../Vector2.h"

class Transform : public Component
{
public:
	Vector2 position;
	float rotation = 0.0f;
	Vector2 scale;

	Vector2 right = Vector2(cos(rotation), -sin(rotation));
	Vector2 forward = Vector2(sin(rotation), cos(rotation));

	Transform()
	{
		position.x = 0.0f;
		position.y = 0.0f;
		rotation = 0.0f;
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
	}

	void SetRotation(const float angle)
	{
		rotation = angle;
	}

	void Update() override
	{
		right = Vector2::Right.Rotate(rotation);
		forward = Vector2::Forward.Rotate(rotation);
		// These lines would run faster, but I gave preference to use the rotation method from the library
		//right = Vector2(cos(rotation ), sin(rotation ));
		//forward = Vector2(-sin(rotation ), cos(rotation ));
	}
};