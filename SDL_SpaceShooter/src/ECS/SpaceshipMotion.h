#pragma once
#include "../Vector2.h"
#include "ECS.h"
#include "Transform.h"
#include "../WindowLoop.h"

class SpaceshipMotion : public Component
{
private:
	Transform* transform;

	float torque;
	float rotationSpeed = 0.12f;

	float thrust;
	float thrustSpeed = 0.10f;
	float drag = 0.008f;

	Vector2 velocity = Vector2::Zero;
	float maxSpeed = 4.0f;

public:

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

	void AddTorque(const float inputTorque)
	{
		this->torque = inputTorque;

		transform->rotation += inputTorque * rotationSpeed;
	}

	void AddThrust(const float inputThrust)
	{
		if (abs(inputThrust) < 0.001f)
		{
			thrust = 0.0f;
			return;
		}

		thrust += inputThrust * thrustSpeed;
		velocity += thrust * transform->forward;
	}

private:

	void MovementLogic()
	{
		velocity.ClampMagnitude(maxSpeed);

		transform->position += velocity;
		velocity -= velocity * drag;

		WindowLoop::LoopOnWindow(transform);
	}

public:

	void Update() override
	{
		MovementLogic();
	}
};