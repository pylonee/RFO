#include "screen.h"
#include <conio.h>

void screen::clear_screen()
{
	system("cls");
}

void screen::move_cursor_to_zero()
{
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 0;
	position.Y = 0;
	SetConsoleCursorPosition(hConsole, position);
}

void screen::menu()
{
	std::cout << "SNAKE\n\n";
	std::cout << "For move use wasd or 5123 on numpad\n\n";
	std::cout << "Press S to start\n\n";

	while (!_kbhit())
	{
		if (_getch() == 's') break;
	}

	this->clear_screen();
}

void screen::gameover_menu(const int score)
{
	std::cout << "HA-HA YOU SUCK!!!!" << std::endl;
	std::cout << "Your score is: " << score << std::endl;
	std::cout << "Press R to restart or Q to quit" << std::endl;
}

bool screen::update_frame(const int map_size, const int map_width, const int  map_height, int* map_coords, snakeBody& snake, food &food)
{
	bool update = false;
	switch (snake.get_direction())
	{
	case 0:	//w
		update = snake.move(0, -1, map_width, map_height, map_coords, food);
		break;

	case 1:	//a
		update = snake.move(-1, 0, map_width, map_height, map_coords, food);
		break;

	case 2:	//s
		update = snake.move(0, 1, map_width, map_height, map_coords, food);
		break;

	case 3:	//d
		update = snake.move(1, 0, map_width, map_height, map_coords, food);
		break;

	default:
		update = snake.move(0, -1, map_width, map_height, map_coords, food);
		break;
	}

	for (int i = 0; i < map_size-1; i++)
	{
		if (map_coords[i] > 0) map_coords[i]--;
	}

	return update;
}


