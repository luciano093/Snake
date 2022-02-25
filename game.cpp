#include"Game.h"

namespace Main {
	bool running = true;
	int delay = 100;
}

Snake snake;
Window window("Snake", 500, 500);
Square apple;

int collision_number = 0;

SDL_Event event;

void start() {
	window.createGrid(20, 20);

	snake = Snake(window.getRenderer(), 200, 200, window.getGridSize(), window.getGridSize());
	apple = Square(window.getRenderer(), 250, 250, window.getGridSize(), window.getGridSize(), 255, 0, 0);
}

void update() {
	handleEvents();

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
		std::cout << "Collision: " << ++collision_number << std::endl;
		snake.setSize(1);
	}

	window.updateTextures(snake.getTextures(), snake.getRects());
	window.updateTexture(apple.getTexture(), apple.getRect());

	window.present();
}

void handleOutOfScreen(Window& window, Snake& snake) {
	if (snake.x < 0) snake.x = window.getWidth() - snake.getWidth();
	else if (snake.x > (window.getWidth() - snake.getWidth())) snake.x = 0;
	if (snake.y < 0) snake.y = window.getHeight() - snake.getHeight();
	else if (snake.y > (window.getHeight() - snake.getHeight())) snake.y = 0;
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
	return snake.x == apple.getX() && snake.y == apple.getY();
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

void handleEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Main::running = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (snake.getSize() == 1 || snake.getDirection() != Snake::Directions::RIGHT) snake.goLeft();
				break;
			case SDLK_RIGHT:
				if (snake.getSize() == 1 || snake.getDirection() != Snake::Directions::LEFT) snake.goRight();
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
				Main::delay -= 10;
				std::cout << "Speed increased" << std::endl;
				break;
			case SDLK_MINUS:
				Main::delay += 10;
				std::cout << "Speed decreased" << std::endl;
				break;
			}
		default:
			break;
		}
	}
}