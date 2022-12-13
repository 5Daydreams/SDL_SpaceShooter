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

	void Update() override
	{
		velocity.ClampMagnitude(maxSpeed);

		transform->position += velocity;

		velocity -= velocity * drag;

		// Perform the loop around the map's edges

		WindowLoop::LoopOnWindow(transform);
	}
};