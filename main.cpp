#pragma warning(push, 0)
#include<SDL.h>
#pragma warning(pop)

#include<iostream>
#include<ctime>
#include"Game.h"

int main(int argv, char* argc[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) std::cerr << "SDL_Init has failed to initialize! " << SDL_GetError() << std::endl;
	
	unsigned lastTime = 0;
	unsigned currentTime;

	Main::running = true;
	Main::delay = 100;

	start();

	while (Main::running) {
		currentTime = SDL_GetTicks();

		if (currentTime > lastTime + Main::delay) {
			update();
			lastTime = currentTime;
		}
	}

	return 0;
}