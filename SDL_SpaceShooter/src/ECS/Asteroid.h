#pragma once
#include "../Vector2.h"
#include "ECS.h"
#include "Transform.h"
#include "../WindowLoop.h"
#include "../Random.h"

class Asteroid : public Component
{
private:
	Transform* transform;
	Vector2 velocity = Vector2::Zero;
	const float maxSpeed = 5.0f;
	int size;

public:
	float rotationSpeed = 0.1f;

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();

		velocity = {
			Random::RealRange(-3.0f,3.0f),
			Random::RealRange(-3.0f,3.0f)
		};

		velocity.ClampMagnitude(maxSpeed);

		if (velocity.Magnitude() < 0.2f)
		{
			velocity *= 10.0f;
		}
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