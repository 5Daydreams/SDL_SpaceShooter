#include "GameObject.h"

Game::Game()
{
}

Game::~Game()
{
}

GameObject::GameObject(const char* textureSheet)
{
	objectTexture = IMG_LoadTexture(Game::renderer, textureSheet);

	xPos = 0;
	yPos = 0;
}

void GameObject::SetPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
}

void GameObject::Update()
{
	SetPosition(++xPos, ++yPos);

	srcRect.w = 64;
	srcRect.h = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos - srcRect.w / 2;
	destRect.y = yPos - srcRect.h / 2;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}