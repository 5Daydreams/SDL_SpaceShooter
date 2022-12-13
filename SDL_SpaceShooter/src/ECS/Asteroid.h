#pragma once
#include "../Vector2.h"
#include "ECS.h"
#include "Transform.h"
#include "../WindowLoop.h"

class Asteroid : public Component
{
private:
	Transform* transform;
	Vector2 velocity = Vector2::Zero;
	const float minSpeed = 1.0f;
	const float maxSpeed = 5.0f;
	int size;

public:
	float rotationSpeed = 0.1f;

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
	}

	Vector2 GetVelocity()
	{
		return velocity;
	}

	void SetVelocity(Vector2 newVel)
	{
		velocity = newVel;
	}

	void SetRotationSpeed(const float rotSpeed)
	{
		transform->rotation += rotSpeed;
	}

	void Update() override
	{
		velocity.ClampMagnitude(maxSpeed);

		transform->position += velocity;

		WindowLoop::LoopOnWindow(transform);
	}
};