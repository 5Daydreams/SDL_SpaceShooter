#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{

public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(float x, float y, float w, float h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;


		switch (tileID)
		{
		case 0:
			path = "assets/water.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/dirt.png";
			break;
		default:
			break;
		}
	}

	void Init() override
	{
		entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, Vector2(1.0f,1.0f));
		transform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(path);
		sprite = &entity->GetComponent<SpriteComponent>();
	}

};
