#include<SDL.h>
#include<iostream>
#include"Window.h"
#include"Square.h"

namespace Game {
	constexpr int GRID_SIZE = 10;

	void handleEvents(const SDL_Keycode& key) {

	}
}

namespace Main {

}

int main(int argc, char* argv[]) {
	Window window("Snake", 500, 500);
	window.createGrid(Game::GRID_SIZE, Game::GRID_SIZE);

	Square s(window.getRenderer(), Game::GRID_SIZE / 2 * window.getGridSize(), Game::GRID_SIZE / 2 * window.getGridSize(), window.getGridSize(), window.getGridSize(), 255, 0, 0);

	SDL_Event evt;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) running = false;
			if (evt.type == SDL_KEYDOWN) Game::handleEvents(evt.key.keysym.sym);
		}

		window.clear();

		window.updateTexture(s.getTexture(), s.getRect());

		window.present();
	}

	return 0;
}