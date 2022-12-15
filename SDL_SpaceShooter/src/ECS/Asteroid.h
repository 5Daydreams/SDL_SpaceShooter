#pragma once
#include "../Vector2.h"
#include "ECS.h"
#include "Health.h"
#include "Transform.h"
#include "../WindowLoop.h"
#include "../Random.h"

class Asteroid : public Component
{
private:
	Transform* transform;
	Health* health;

	const float maxSpeed = 5.0f;
	Vector2 velocity = Vector2::Zero;
	float rotationSpeed = 0.07f;

	int splitSize;

	const std::function<void()> deathCallback = [this]()
	{
		std::cout << "Asteroid died" << std::endl;
		entity->Destroy();
	};

public:

	Asteroid() : splitSize(1) {}

	Asteroid(int size) : splitSize(size) {}

	~Asteroid() {}

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

private:

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

	void MovementLogic()
	{
		velocity.ClampMagnitude(maxSpeed);

		transform->position += velocity;
		transform->rotation += rotationSpeed;

		WindowLoop::LoopOnWindow(transform);
	}

public:

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
		health = &entity->GetComponent<Health>();

		health->SubscribeToDeathCallback(deathCallback);

		RandomizeVelocity();
	}

	void Update() override
	{
		MovementLogic();
	}
};