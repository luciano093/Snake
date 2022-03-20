#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include"Snake.h"
#include"Square.h"
#include"Main.h"
#include<cstdlib>
#include<time.h>

namespace Game {
	extern Snake* snake;
	extern Square* apple;

	extern void handleEvents(const SDL_Keycode& key);
	extern void start();
	extern void update();
}

#endif
