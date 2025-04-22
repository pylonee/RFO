#pragma once

class defaultSettings
{
public:
	int get_map_width();
	int get_map_height();
	int get_map_size();
	int get_snake_speed();

	char get_walls_img();
	char get_snake_head_img();
	char get_snake_dead_img();
	char get_food_img();
	char get_object_img(int code);

private:
	int map_width = 30, map_height = 15, map_size = map_width * map_height, snake_speed = 6;
	char walls_img = '+', snake_head_img = 'o', snake_dead_img = '*', food_img = '·';
};

