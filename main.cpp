#include<SDL.h>
#include<iostream>
#include"Square.h"
#include"Game.h"
#include"Config.h"
#include"Main.h"

Window Main::window("Snake", 500, 500);

unsigned lastTime = 0;
unsigned currentTime;
int delay = 90;

int main(int argc, char* argv[]) {
	
	Main::window.createGrid(GRID_SIZE, GRID_SIZE);

	SDL_Event evt;
	bool running = true;

	Game::start();

	while (running) {
		currentTime = SDL_GetTicks();

		if (currentTime > lastTime + delay) {
			while (SDL_PollEvent(&evt)) {
				if (evt.type == SDL_QUIT) running = false;
				if (evt.type == SDL_KEYDOWN) {
					if (evt.key.keysym.sym == SDLK_EQUALS) delay -= 10;
					else if(evt.key.keysym.sym == SDLK_MINUS) delay += 10;
					else Game::handleEvents(evt.key.keysym.sym);
				}
			}

			Main::window.clear();

			Game::update();

			Main::window.present();

			lastTime = currentTime;
		}
	}

	return 0;
}