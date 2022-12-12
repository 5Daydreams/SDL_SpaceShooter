#pragma once
#include "../Vector2.h"

class ProjTransform
{
public:
	Vector2 position;
	float rotation = 0.0f;
	Vector2 scale;

	Vector2 right = Vector2(cos(rotation), -sin(rotation));
	Vector2 forward = Vector2(sin(rotation), cos(rotation));

	ProjTransform()
	{
		position.x = 0.0f;
		position.y = 0.0f;
		rotation = 0.0f;
		scale.x = 1.0f;
		scale.y = 1.0f;
	}

	ProjTransform(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	ProjTransform(Vector2 pos)
	{
		position = pos;
	}

	ProjTransform(float x, float y, Vector2 scale)
	{
		this->position.x = x;
		this->position.y = y;
		this->scale = scale;
	}

	ProjTransform(float xPos, float yPos, float xScale, float yScale)
	{
		this->position.x = xPos;
		this->position.y = yPos;
		this->scale.x = xScale;
		this->scale.y = yScale;
	}

	ProjTransform(Vector2 pos, Vector2 scale)
	{
		this->position = pos;
		this->scale = scale;
	}

	void Init()
	{
	}

	void SetRotation(const float angle)
	{
		rotation = angle;
	}

	void Update()
	{
		right = Vector2(cos(rotation ), sin(rotation ));
		forward = Vector2(-sin(rotation ), cos(rotation ));
	}
};