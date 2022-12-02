#pragma once
#include "Game.h"
#include <array>

class Map
{
public:
	Map();
	~Map();

	void LoadMap(std::array<std::array<int, 25>, 20> arr);
	void DrawMap();

private:

	SDL_Rect srcR, destR;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	std::array<std::array<int, 25>, 20> map; // declare an integer array with length 3
};