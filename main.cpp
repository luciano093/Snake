#include<SDL.h>
#include<iostream>
#include<ctime>
#include"Config.h"
#include"Game.h"
#include"Layers/Layer.h"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) std::cerr << "SDL_Init has failed to initialize! " << SDL_GetError() << std::endl;
	
	unsigned lastTime = 0;
	unsigned currentTime;

	int i = GRID_SIZE;
	std::cout << i << std::endl;
	Game::start();

	while (Game::running) {
		currentTime = SDL_GetTicks();

		if (currentTime > lastTime + Game::delay) {
			Game::handleEvents();
			Game::window.clear();
			Game::window.presentGrid();
			Game::update();
			Game::window.present();

			lastTime = currentTime;
		}
	}

	return 0;
}    