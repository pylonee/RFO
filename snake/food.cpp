#include "food.h"

int food::get_coord_x()
{
	return this->food_coord_x;
}

int food::get_coord_y()
{
	return this->food_coord_y;
}

int food::get_amount()
{
	return this->food_amount;
}

void food::increase_amount()
{
	this->food_amount++;
}

void food::set_food_coords(const int new_coord_x, const int new_coord_y)
{
	this->food_coord_x = new_coord_x;
	this->food_coord_y = new_coord_y;
}

void food::create_food(const int map_width, const int map_height, int *map_coords)
{
	srand(time(0));

	int food_x, food_y;

	do
	{
		food_x = rand() % (map_width - 1);
		food_y = rand() % (map_height - 1);
	} while (map_coords[map_height * food_x + food_y] != 0);

	this->set_food_coords(food_x, food_y);
	map_coords[map_height * food_x + food_y] = -5;
}
