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
	int size = 3;
	int currentHealth = 10;

public:
	float rotationSpeed = 0.07f;

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

	void DamageThis()
	{
		currentHealth--;

		if(currentHealth <= 0)
		{
			entity->Destroy();
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
		transform->rotation += rotationSpeed;

		WindowLoop::LoopOnWindow(transform);
	}
};