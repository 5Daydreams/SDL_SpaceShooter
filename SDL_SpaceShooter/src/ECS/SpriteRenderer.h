#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteRenderer : public Component
{
private:
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	float rotation = 0.0f;

public:

	SpriteRenderer() = default;

	~SpriteRenderer()
	{
		SDL_DestroyTexture(texture);
	}

	SpriteRenderer(const char* path)
	{
		texture = IMG_LoadTexture(Game::renderer, path);
	}

	void Init() override
	{
		transform = &entity->GetComponent<Transform>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = 64;
		srcRect.h = 64;
	}

	void Update() override
	{
		destRect.w = 64 * transform->scale.x;
		destRect.h = 64 * transform->scale.y;
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
		double finalRotation = (transform->rotation + rotation) * 180.f / 3.14f;
		SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, finalRotation, NULL, SDL_FLIP_NONE);
	}
};