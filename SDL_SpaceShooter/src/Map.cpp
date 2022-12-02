#include "Map.h"

std::array<std::array<int, 25>, 20> _level1 = { {
	{2,1,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,1,1,1,1,1,1,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0},
	{2,0,0,0,2,1,2,0,0,0,0,0,0,2,1,2,0,0,2,0,0,0,0,0,0}
	} };

Map::Map()
{
	std::string dirtPath = "assets/dirt.png";
	std::string grassPath = "assets/grass.png";
	std::string waterPath = "assets/water.png";

	/* order: water == 0, grass == 1, dirt == 2 */
	water = IMG_LoadTexture(Game::renderer, waterPath.c_str());
	grass = IMG_LoadTexture(Game::renderer, grassPath.c_str());
	dirt = IMG_LoadTexture(Game::renderer, dirtPath.c_str());

	LoadMap(_level1);

	srcR.x = srcR.y = 0;
	srcR.w = srcR.h = 64;
	destR.w = destR.h = 64;

	destR.x = destR.y = 0;
}

Map::~Map()
{
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(dirt);
}

void Map::LoadMap(std::array<std::array<int, 25>, 20> arr)
{
	const int rowRange = arr.size();
	const int columnRange = arr[0].size();

	const int rows = rowRange;
	const int cols = columnRange;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = arr[i][j];
		}
	}
}

void Map::DrawMap()
{
	const int rows = map.size();
	const int cols = map[0].size();

	int type = 0;

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			type = map[j][i];

			destR.x = i * 32;
			destR.y = j * 32;

			switch (type)
			{
			case 0:
				SDL_RenderCopy(Game::renderer, water, &srcR, &destR);
				break;
			case 1:
				SDL_RenderCopy(Game::renderer, grass, &srcR, &destR);
				break;
			case 2:
				SDL_RenderCopy(Game::renderer, dirt, &srcR, &destR);
				break;
			default:
				break;
			}
		}
	}
}
