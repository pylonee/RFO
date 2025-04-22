#pragma once

#include "food.h"

class snakeBody
{
public:
	int get_head_coord_x();
	int get_head_coord_y();
	int get_direction();

	void set_head_coords(const int new_coord_x, const int new_coord_y);
	void change_direction(const char key);
	bool move(const int direction_x, const int direction_y, const int map_width, const int map_height, int* map_coords, food &food);
private:
	int head_coord_x = 0, head_coord_y = 0, direction = 0;
};