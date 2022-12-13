#pragma once
#include "../Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "ECS.h"
#include "Transform.h"

class SpriteRenderer : public Component
{
private:
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	float rotation = 0.0f;

public:
	bool isActive = false;

	SpriteRenderer() = default;

	~SpriteRenderer()
	{
		SDL_DestroyTexture(texture);
	}

	SpriteRenderer(const char* path)
	{
		texture = IMG_LoadTexture(Game::renderer, path);
	}

	void DisableRenderer()
	{
		isActive = false;
	}

	bool IsActive()
	{
		return isActive;
	}

	void Init() override
	{
		if (&entity->GetComponent<Transform>() == nullptr)
		{
			&entity->AddComponent<Transform>();
		}
		transform = &entity->GetComponent<Transform>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = 64;
		srcRect.h = 64;

		isActive = true;
	}

	void Update() override
	{
		if (!isActive)
		{
			return;
		}

		destRect.w = static_cast<int>(64 * transform->scale.x);
		destRect.h = static_cast<int>(64 * transform->scale.y);
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
	}

	void RotateSprite(float angle)
	{
		rotation += angle;
	}

	void SetSpriteRotation(float angle)
	{
		rotation = angle;
	}

	void Draw()	override
	{
		if (!isActive)
		{
			return;
		}

		double finalRotation = (transform->rotation + rotation) * 180.f / 3.14f;
		SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, finalRotation, NULL, SDL_FLIP_NONE);
	}
};