#include<SDL.h>
#include<iostream>
#include"Window.h"

namespace Game {
	constexpr int GRID_SIZE = 10;

	void handleEvents(const SDL_Event& evt) {
		 
	}
}

namespace Main {

}

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) std::cerr << "SDL has failed to initialize video " << SDL_GetError() << std::endl;

	Window window("Snake", 500, 500);
	window.createGrid(Game::GRID_SIZE, Game::GRID_SIZE);

	SDL_Event evt;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) running = false;
			Game::handleEvents(evt);
		}

		window.clear();
		window.presentGrid();



		window.present();
	}

	return 0;
}