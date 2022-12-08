#pragma once
#include "../Vector2.h"
#include "ECS.h"
#include "Transform.h"

class SpaceshipMotion : public Component
{
private:
	Transform* transform;
	float thrust;
	float torque;
	float maxSpeed = 3.0f;
	Vector2 velocity = Vector2::Zero;

public:
	float thrustSpeed = 0.05f;
	float rotationSpeed = 0.1f;
	float drag = 0.01f;

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
	}
};