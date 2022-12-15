#pragma once
#include "SDL_image.h"
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet);
	~GameObject();

	void SetPosition(int x, int y);

	void Update();
	void Render();

private:
	int xPos, yPos;
	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
};