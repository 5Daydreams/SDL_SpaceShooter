#pragma once
#include "../Vector2.h"
#include "ECS.h"
#include "Health.h"
#include "SpaceshipMotion.h"
#include "Transform.h"
#include "../WindowLoop.h"

class Player : public Component
{
private:
	SpaceshipMotion* spaceship;
	Health* health;

	const std::function<void()> deathCallback = [this]()
	{
		std::cout << "Player died" << std::endl;
		entity->Destroy();
	};

public:

	void Init() override
	{
		spaceship = &entity->GetComponent<SpaceshipMotion>();
		health = &entity->GetComponent<Health>();

		health->SubscribeToDeathCallback(deathCallback);
	}

	void Update() override
	{

	}
};