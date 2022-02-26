#include<SDL.h>
#include<iostream>
#include<ctime>
#include"Game.h"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) std::cerr << "SDL_Init has failed to initialize! " << SDL_GetError() << std::endl;
	
	unsigned lastTime = 0;
	unsigned currentTime;

	Game::start();

	while (Game::running) {
		currentTime = SDL_GetTicks();

		if (currentTime > lastTime + Game::delay) {
			Game::update();
			lastTime = currentTime;
		}
	}

	return 0;
}    