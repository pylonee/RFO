#include "snakeBody.h"

int snakeBody::get_head_coord_x()
{
	return this->head_coord_x;
}

int snakeBody::get_head_coord_y()
{
	return this->head_coord_y;
}

int snakeBody::get_direction()
{
	return this->direction;
}

void snakeBody::set_head_coords(const int new_coord_x, const int new_coord_y)
{
	this->head_coord_x = new_coord_x;
	this->head_coord_y = new_coord_y;
}

void snakeBody::change_direction(const char key)
{
	switch (key)
	{
	case 'w':
		if (this->direction != 2) this->direction = 0;
		break;
	case 'a':
		if (this->direction != 3) this->direction = 1;
		break;
	case 's':
		if (this->direction != 0) this->direction = 2;
		break;
	case 'd':
		if (this->direction != 1) this->direction = 3;
		break;
	case '5':
		if (this->direction != 2) this->direction = 0;
		break;
	case '1':
		if (this->direction != 3) this->direction = 1;
		break;
	case '2':
		if (this->direction != 0) this->direction = 2;
		break;
	case '3':
		if (this->direction != 1) this->direction = 3;
		break;
	default:
		break;
	}
}

bool snakeBody::move(const int direction_x, const int direction_y, const int map_width, const int map_height, int* map_coords, food& food)
{
	this->head_coord_x = this->head_coord_x + direction_x;
	this->head_coord_y = this->head_coord_y + direction_y;

	if (map_coords[map_height * this->head_coord_x + this->head_coord_y] == -5)
	{
		food.increase_amount();
		food.create_food(map_width, map_height, map_coords);
	}

	if (map_coords[map_height * this->head_coord_x + this->head_coord_y] == -100 || map_coords[map_height * this->head_coord_x + this->head_coord_y] > 0)
	{
		map_coords[map_height * this->head_coord_x + this->head_coord_y] = -1;
		return false;
	}

	map_coords[map_height * this->head_coord_x + this->head_coord_y] = food.get_amount() + 1;
	return true;
}
