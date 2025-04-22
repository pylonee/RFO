#pragma once

#include <iostream>
#include <ctime>

class food
{
public:
	int get_coord_x();
	int get_coord_y();
	int get_amount();

	void increase_amount();
	void set_food_coords(const int new_coord_x, const int new_coord_y);
	void create_food(const int map_width, const int map_height, int* map_coords);

private:
	int food_coord_x = 0, food_coord_y = 0, food_amount = 1;
};

