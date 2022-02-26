#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<array>
#include"Snake.h"
#include"Window.h"
#include"Config.h"
#include"Entity.h"

namespace Game {
	extern Window window;

	extern bool running;
	extern int delay;

	extern void start();
	extern void update();
	extern void handleEvents();

	extern bool isOutOfScreen(std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>& grid, Snake& snake);
	extern void handleOutOfScreen(std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>& grid, Snake& snake);
	extern void giveAppleRandPos(Window& window, Snake& snake, Entity& apple);
	extern bool checkSnakeTailCollision(Snake& snake);

	void populateGrid(std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>& grid);
}

#endif