#include "defaultSettings.h"

int defaultSettings::get_map_width()
{
	return this->map_width;
}

int defaultSettings::get_map_height()
{
	return this->map_height;
}

int defaultSettings::get_map_size()
{
	return this->map_size;
}

int defaultSettings::get_snake_speed()
{
	return this->snake_speed;
}

char defaultSettings::get_walls_img()
{
	return this->walls_img;
}

char defaultSettings::get_snake_head_img()
{
	return this->snake_head_img;
}

char defaultSettings::get_snake_dead_img()
{
	return this->snake_dead_img;
}

char defaultSettings::get_food_img()
{
	return this->food_img;
}

char defaultSettings::get_object_img(int code)
{
	if (code > 0) 
	{
		return this->snake_head_img;
	}
	switch (code)
	{
	case -1:
		return this->snake_dead_img;
		break;

	case -5:
		return this->food_img;
		break;

	case -100:
		return this->walls_img;
		break;

	default:
		return ' ';
		break;
	}
}
