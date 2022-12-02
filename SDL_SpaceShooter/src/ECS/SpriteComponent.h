#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	SpriteComponent(const char* path)
	{
		texture = IMG_LoadTexture(Game::renderer, path);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

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

	void Draw()	override
	{
		SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
	}
};