#pragma once

#include <iostream>
#include <windows.h>

#include "snakeBody.h"

class screen
{
public:
	void clear_screen();
	void move_cursor_to_zero();
	void menu();
	void gameover_menu(const int score);
	bool update_frame(const int map_size, const int map_width, const int  map_height, int* map_coords, snakeBody& snake, food& food);
private:
	
};

