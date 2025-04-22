#include <iostream>
#include <conio.h>

#include "defaultSettings.h"
#include "gameMap.h"
#include "snakeBody.h"
#include "food.h"
#include "screen.h"

void startGame()
{
	setlocale(LC_ALL, "ru");

	defaultSettings defSet; gameMap gMap; snakeBody snake; food apple; screen sc;

	sc.clear_screen();
	sc.menu();
	
	const int fps = 1000 / defSet.get_snake_speed();

	const int map_size = defSet.get_map_size();
	int* game_map_coords = new int[map_size] {};

	gMap.create_map(defSet.get_map_width(), defSet.get_map_height(), game_map_coords, apple, snake);
	gMap.drawMap(game_map_coords, apple.get_amount() - 1);

	while (!_kbhit())
	{
		if (_getch() == 'w' || _getch() == 'a' || _getch() == 's' || _getch() == 'd' || _getch() == '5' || _getch() == '1' || _getch() == '2' || _getch() == '3') break;
	}

	bool endGame = false;

	while (!endGame)
	{
		if (_kbhit())
		{
			snake.change_direction(_getwch());
		}
		//sc.clear_screen();
		sc.move_cursor_to_zero();

		endGame = !sc.update_frame(map_size, defSet.get_map_width(), defSet.get_map_height(), game_map_coords, snake, apple);

		gMap.drawMap(game_map_coords, apple.get_amount() - 1);

		Sleep(fps);
	}

	delete[] game_map_coords;

	sc.gameover_menu(apple.get_amount() - 1);

	while (!_kbhit())
	{
		if (_getch() == 'r') startGame();
		if (_getch() == 'q') break;
	}
}

int main()
{			
	startGame();
	return 0;
}