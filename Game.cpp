#include"Game.h"

namespace Game {
	Snake* snake;
	Square* apple;

	bool isGrowing = false;

	bool isSnakeOnScreen();
	bool hasSnakeCollided();
	void updateApplePos();

	void handleEvents(const SDL_Keycode& key) {
		switch (key) {
		case SDLK_UP: snake->direction = Snake::Direction::UP; break;
		case SDLK_DOWN: snake->direction = Snake::Direction::DOWN; break;
		case SDLK_LEFT: snake->direction = Snake::Direction::LEFT; break;
		case SDLK_RIGHT: snake->direction = Snake::Direction::RIGHT; break;
		case SDLK_SPACE: snake->grow(); isGrowing = true; break;
		}
	}

	void start() {
		int snakeInitialPos = GRID_SIZE * Main::window.getGridSize() / 2;
		int appleInitialPos = Main::window.getGridSize() * 3;

		snake = new Snake(snakeInitialPos, snakeInitialPos, Main::window.getGridSize(), Main::window.getGridSize());
		apple = new Square(Main::window.getRenderer(), appleInitialPos, appleInitialPos, Main::window.getGridSize(), Main::window.getGridSize(), SDL_Color{255, 0, 0});
	}

	void update() {
		if (isSnakeOnScreen() && (!hasSnakeCollided() || isGrowing)) {
			isGrowing = false;
			snake->move();
		}
		else {
			int snakeInitialPos = GRID_SIZE * Main::window.getGridSize() / 2;
			snake->reset(snakeInitialPos, snakeInitialPos);
		}

		if (snake->getX() == apple->getX() && snake->getY() == apple->getY()) {
			snake->grow();
			isGrowing = true;
			updateApplePos();
		}

		for (const Square* square : snake->getParts()) {
			Main::window.updateTexture(square->getTexture(), square->getRect());
		}

		Main::window.updateTexture(apple->getTexture(), apple->getRect());
	}

	bool isSnakeOnScreen() {
		return (snake->direction == Snake::Direction::UP && snake->getY() > 0) || (snake->direction == Snake::Direction::DOWN && snake->getY() < Main::window.getHeight() - Main::window.getGridSize()) || (snake->direction == Snake::Direction::LEFT && snake->getX() > 0) || (snake->direction == Snake::Direction::RIGHT && snake->getX() < Main::window.getWidth() - Main::window.getGridSize());
	}

	bool hasSnakeCollided() {
		const Square* const head = snake->getHead();

		// Check collision with body
		for (auto i = ++snake->getParts().cbegin(); i != snake->getParts().cend(); ++i) {
			if (head->getX() == (*i)->getX() && head->getY() == (*i)->getY()) return true;
		}

		return false;
	}

	void updateApplePos() {
		srand(time(nullptr));
		int newX = rand() % GRID_SIZE * Main::window.getGridSize();
		int newY = rand() % GRID_SIZE * Main::window.getGridSize();

		while (true) {
			bool stop = true;

			for (Square* const part : snake->getParts()) {
				if (part->getX() == newX && part->getY() == newY) {
					newX = rand() % GRID_SIZE * Main::window.getGridSize();
					newY = rand() % GRID_SIZE * Main::window.getGridSize();
					stop = false;
				}
			}

			if (stop) break;
		}

		apple->setX(newX);
		apple->setY(newY);
	}
}