#pragma once
#include "../Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "ProjTransform.h"

class ProjectileRenderer
{
private:
	ProjTransform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	float rotation = 0.0f;

public:

	ProjectileRenderer() = default;

	~ProjectileRenderer()
	{
		SDL_DestroyTexture(texture);
	}

	ProjectileRenderer(ProjTransform *tran, const char* path)
	{
		transform = tran;
		texture = IMG_LoadTexture(Game::renderer, path);
		Init();
	}

	void Init()
	{
		srcRect.x = srcRect.y = 0;
		srcRect.w = 64;
		srcRect.h = 64;
	}

	void Update()
	{
		destRect.w = static_cast<int>(32 * transform->scale.x);
		destRect.h = static_cast<int>(32 * transform->scale.y);
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

	void Draw()
	{
		double finalRotation = (transform->rotation + rotation) * 180.f / 3.14f;
		SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, finalRotation, NULL, SDL_FLIP_NONE);
	}
};