#pragma once
#include "Components.h"
#include "../Vector2.h"

class PhysicsMotion : public Component
{
private:
	Transform* transform;
	Vector2 velocity;
	Vector2 bufferedForce;
	float torque;

public:
	float rotationSpeed = 3.0f;
	float speed = 3.0f;
	float drag = 0.5f;

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();
		velocity = Vector2::Zero;
	}

	Vector2 GetVelocity()
	{
		return velocity;
	}

	void SetVelocity(Vector2 newVel)
	{
		velocity = newVel;
	}

	void AddTorque(const float torque)
	{
		this->torque = torque;
	}

	void AddForce(const Vector2 force)
	{
		bufferedForce += force;
	}

	void Update() override
	{
		transform->rotation += torque * rotationSpeed;
		torque = 0;

		velocity += bufferedForce * 0.1f;
		bufferedForce = Vector2::Zero;

		Vector2 rotatedVelocity = velocity.y * transform->forward;

		std::cout << "tr.fwd = " << transform->forward << std::endl;
		std::cout << "velY = " << velocity.y << std::endl;
		std::cout << "rotVel = " << rotatedVelocity << std::endl;
		transform->position += rotatedVelocity * speed;
	}
};