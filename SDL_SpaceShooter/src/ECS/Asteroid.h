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
	Collider2D* collider;

	const float maxSpeed = 5.0f;
	Vector2 velocity = Vector2::Zero;
	float rotationSpeed = 0.07f;

	bool bufferDamage = false;

	int splitSize = 3;
	int currentHealth = 10;

	const std::function<void(const Collider2D&)> collisionCallback = [this](const Collider2D& other)
	{
		if (other.tag == "projectile")
		{
			std::cout << "Asteroid took damage" << std::endl;
			bufferDamage = true;
		}
	};

public:

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

	void RandomizeVelocity()
	{
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

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
		collider = &entity->GetComponent<Collider2D>();

		collider->SubscribeToCollisionCallback(collisionCallback);

		RandomizeVelocity();
	}

private:

	void DamageLogic()
	{
		if (!bufferDamage)
		{
			return;
		}

		bufferDamage = false;

		currentHealth--;

		if (currentHealth <= 0)
		{
			entity->Destroy();
		}
	}

	void MovementLogic()
	{
		velocity.ClampMagnitude(maxSpeed);

		transform->position += velocity;
		transform->rotation += rotationSpeed;

		WindowLoop::LoopOnWindow(transform);
	}

public:

	void Update() override
	{
		MovementLogic();
		DamageLogic();
	}
};