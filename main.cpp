#include<SDL.h>
#include<iostream>
#include<vector>
#include<ctime>
#include"Window.h"
#include"Snake.h"
#include"Square.h"

void handleOutOfScreen(Window& window, Snake& snake);
void giveAppleRandPos(Window& window, Snake& snake, Square& apple);
inline bool checkSnakeAppleCollision(Snake& snake, Square& apple);
bool checkSnakeTailCollision(Snake& snake);

int main(int argv, char* argc[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) std::cerr << "SDL_Init has failed to initialize! " << SDL_GetError() << std::endl;
	Window window("Snake", 500, 500);

	std::vector<SDL_Rect> snakeTexture;
	window.createGrid(20, 20);

	Snake snake(window.getRenderer(), 200, 200, window.getGridSize(), window.getGridSize());
	Square apple(window.getRenderer(), 250, 250, window.getGridSize(), window.getGridSize(), 255, 0, 0);

	SDL_Event event;
	bool running = true;

	int delay = 100;
	unsigned lastTime = 0, currentTime;

	while (running) {
		while(SDL_PollEvent(&event)){
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					if (snake.getSize() == 1 || snake.getDirection() != Snake::Directions::RIGHT) snake.goLeft();
					break;
				case SDLK_RIGHT:
					if(snake.getSize() == 1 || snake.getDirection() != Snake::Directions::LEFT) snake.goRight();
					break;
				case SDLK_UP:
					if (snake.getSize() == 1 || snake.getDirection() != Snake::Directions::DOWN) snake.goUp();
					break;
				case SDLK_DOWN:
					if (snake.getSize() == 1 || snake.getDirection() != Snake::Directions::UP) snake.goDown();
					break;
				case SDLK_SPACE:
					snake.grow();
					break;
				case SDLK_LSHIFT:
					// nothing happens :(
					// this may trigger autosnake (maybe)
					break;
				case SDLK_EQUALS:
					delay -= 10;
					std::cout << "Speed increased" << std::endl;
					break;
				case SDLK_MINUS:
					delay += 10;
					std::cout << "Speed decreased" << std::endl;
					break;
				}
			default:
				break; 
			} 
		}

		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + delay) {

			window.clear();
			window.presentGrid();
		
			snake.move();
		
			// When snake goes out of screen
			handleOutOfScreen(window, snake);
		
			// when snake collides with apple
			if (checkSnakeAppleCollision(snake, apple)) {
				snake.grow();
				giveAppleRandPos(window, snake, apple);
			}

			// collision with tail
			if (snake.getSize() > 3 && checkSnakeTailCollision(snake)) {
				 // Code to kill
				std::cout << "Colision" << std::endl;
			}

			window.updateTextures(snake.getTextures(), snake.getRects());
			window.updateTexture(apple.getTexture(), apple.getRect());

			window.present();

			lastTime = currentTime;
		}
	}

	window.quit();

	return 0;
}

void handleOutOfScreen(Window& window, Snake& snake) {
	if (snake.getX() < 0) snake.setX(window.getWidth() - snake.getWidth());
	else if (snake.getX() > (window.getWidth() - snake.getWidth())) snake.setX(0);
	if (snake.getY() < 0) snake.setY(window.getHeight() - snake.getHeight());
	else if (snake.getY() > (window.getHeight() - snake.getHeight())) snake.setY(0);
}

void giveAppleRandPos(Window& window, Snake& snake, Square& apple) {
	srand(time(0) + rand()); // updates seed using current time

	do {
		bool unpassed = false;

		//Set random position
		apple.setX((rand() % window.getRows()) * window.getGridSize());
		apple.setY((rand() % window.getCols()) * window.getGridSize());

		for (Square& s : snake.getSquares()) {
			if (s.getX() == apple.getX() && s.getY() == apple.getY()) {
				unpassed = true;
				break;
			}
		} 
		if (!unpassed) break;
	} while (true);
}

inline bool checkSnakeAppleCollision(Snake& snake, Square& apple) {
	return snake.getX() == apple.getX() && snake.getY() == apple.getY();
}

bool checkSnakeTailCollision(Snake& snake) {
	Square* head = snake.getHead();

	for (Square& s : snake.getSquares()) {
		if (&s == head) continue;
		else if (s == *head) {
			return true;
		}
	}

	return false;
}