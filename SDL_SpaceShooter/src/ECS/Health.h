#pragma once
#include "Collider.h"
#include "ECS.h"
#include "../Random.h"

class Health : public Component
{
private:
	Collider2D* collider;

	bool bufferDamage = false;
	int currentHealth = 10;

	std::vector<std::function<void()>> onDeath = std::vector<std::function<void()>>{};

	const std::function<void(const Collider2D&)> collisionCallback = [this](const Collider2D& other)
	{
		if (other.tag == "projectile")
		{
			bufferDamage = true;
		}
	};

public:

	Health() {}

	~Health() {}

	void Init() override
	{
		collider = &entity->GetComponent<Collider2D>();

		collider->SubscribeToCollisionCallback(collisionCallback);
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
		std::cout << "Entity took damage" << std::endl;

		if (currentHealth <= 0)
		{
			TriggerDeathCallback();
		}
	}

public:

	void Update() override
	{
		DamageLogic();
	}

	void SubscribeToDeathCallback(const std::function<void()>& callback)
	{
		onDeath.push_back(callback);
	}

private:

	void TriggerDeathCallback() const
	{
		for (const auto& callback : onDeath)
		{
			callback();
		}
	}
};