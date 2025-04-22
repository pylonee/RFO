#pragma once

#include "defaultSettings.h"
#include "snakeBody.h"
#include "food.h"

class gameMap
{
public:
	void create_map(int map_width, int map_height, int *map_coords, food &food, snakeBody &snake);
	void drawMap(int* map_coords, int score);

private:
	int map_height, map_width, map_size;
};

