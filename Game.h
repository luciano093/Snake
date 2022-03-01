#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<array>
#include"Snake.h"
#include"Window.h"
#include"Config.h"
#include"Entity.h"
#include"Layers/Layer.h"
#include"Ai.h"

namespace Game {
	extern Window window;

	extern bool running;
	extern int delay;

	extern void start();
	extern void update();
	extern void handleEvents();

	extern bool isOutOfScreen(array2d& grid, Snake& snake);
	extern void handleOutOfScreen(array2d& grid, Snake& snake);
	extern void giveAppleRandPos(Window& window, Snake& snake, Entity& apple);
	extern bool checkSnakeTailCollision(Snake& snake);

	extern void handleSnakeDeath();
	extern void populateGrid(std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>& grid);
}

#endif