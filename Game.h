#ifndef GAME_H
#define GAME_H

#include"Snake.h"
#include"Window.h"

namespace Main {
	
}

extern void start();
extern void update();

extern void handleEvents();

extern void handleOutOfScreen(Window& window, Snake& snake);
extern void giveAppleRandPos(Window& window, Snake& snake, Square& apple);
extern inline bool checkSnakeAppleCollision(Snake& snake, Square& apple);
extern bool checkSnakeTailCollision(Snake& snake);

#endif