#include "gameMap.h"

/*
	####	0 3 6 9		0 4 8  12	0 5 10 15 20
	#  #	1 4 7 10	1 5 9  13	1 6 11 16 21
	####	2 5 8 11	2 6 10 14	2 7 12 17 22
						3 7 11 15	3 8 13 18 23
									4 9 14 19 24
*/

void gameMap::create_map(int map_width, int map_height, int* map_coords, food &food, snakeBody& snake)
{	
	this->map_width = map_width;
	this->map_height = map_height;

	for (int x = 0; x < map_width; x++)
	{
		map_coords[x * map_height] = -100;
		map_coords[map_height * x + (map_height-1)] = -100;
	}

	for (int  y= 0; y < map_height; y++)
	{
		map_coords[y] = -100;
		map_coords[y + (map_width - 1) * map_height] = -100;
	}

	snake.set_head_coords(map_width / 2, map_height / 2);
	map_coords[map_height * (map_width / 2) + map_height / 2] = 1;

	food.create_food(map_width, map_height, map_coords);
}

void gameMap::drawMap(int* map_coords, int score)
{	
	defaultSettings defSet;

	std::cout << "Snake\t\tScore: " << score << std::endl;

	for (int y = 0; y < this->map_height; y++)
	{
		for (int x = 0; x < this->map_width; x++)
		{
			std::cout << defSet.get_object_img(map_coords[this->map_height * x + y]);
		}
		std::cout << '\n';
	}
}
