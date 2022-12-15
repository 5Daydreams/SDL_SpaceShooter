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

public:

	void Init() override
	{
		spaceship = &entity->GetComponent<SpaceshipMotion>();
		health = &entity->GetComponent<Health>();
	}

	void Update() override
	{
		
	}
};