#include"Game.h"

namespace Game {
	Window window("Snake", 500, 500);
	Snake snake;
	Entity apple;

	std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE> grid;

	bool running = true;
	int delay = 100;

	int collision_number = 0;

	SDL_Event event;

	void start() {
		window.createGrid(GRID_SIZE, GRID_SIZE);

		populateGrid(grid);

		snake = Snake(window.getRenderer(), &grid, GRID_SIZE/2, GRID_SIZE/2, window.getGridSize(), window.getGridSize());
		apple = Entity(window.getRenderer(), &grid, GRID_SIZE - 1, GRID_SIZE - 1, window.getGridSize(), window.getGridSize(), EntityType::FOOD, 255, 0, 0);

		grid[apple.getY()][apple.getX()] = apple.getEntityType();
	}

	void update() {
		handleEvents();
		window.clear();
		window.presentGrid();

		if(snake.getDirection() != Snake::Direction::NONE && !isOutOfScreen(grid, snake)) snake.move();
		else if (isOutOfScreen(grid, snake)) {
			handleOutOfScreen(grid, snake);
		}
		
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

	void handleEvents() {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				Game::running = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					if (snake.getSize() == 1 || snake.getDirection() != Snake::Direction::RIGHT) snake.goLeft();
					break;
				case SDLK_RIGHT:
					if (snake.getSize() == 1 || snake.getDirection() != Snake::Direction::LEFT) snake.goRight();
					break;
				case SDLK_UP:
					if (snake.getSize() == 1 || snake.getDirection() != Snake::Direction::DOWN) snake.goUp();
					break;
				case SDLK_DOWN:
					if (snake.getSize() == 1 || snake.getDirection() != Snake::Direction::UP) snake.goDown();
					break;
				case SDLK_SPACE:
					snake.grow();
					break;
				case SDLK_EQUALS:
					Game::delay -= 10;
					std::cout << "Speed increased" << std::endl;
					break;
				case SDLK_MINUS:
					Game::delay += 10;
					std::cout << "Speed decreased" << std::endl;
					break;
				}
			}
		}
	}

	bool isOutOfScreen(std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>& grid, Snake& snake) {
		switch (snake.getDirection()) {
		case Snake::Direction::LEFT:
			if (snake.getX() <= 0) return true;
			break;
		case Snake::Direction::RIGHT:
			if (snake.getX() >= grid.size() - 1) return true;
			break;
		case Snake::Direction::UP:
			if (snake.getY() <= 0) return true;
			break;
		case Snake::Direction::DOWN:
			if (snake.getY() >= grid.size() - 1) return true;
			break;
		}

		return false;
	}

	void handleOutOfScreen(std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>& grid, Snake& snake) {
		switch (snake.getDirection()) {
		case Snake::Direction::LEFT:
			snake.moveTo(grid.size() - 1, snake.getY());
			break;
		case Snake::Direction::RIGHT:
			snake.moveTo(0, snake.getY());
			break;
		case Snake::Direction::UP:
			snake.moveTo(snake.getX(), grid.size() - 1);
			break;
		case Snake::Direction::DOWN:
			snake.moveTo(snake.getX(), 0);
			break;
		}
	}

	void giveAppleRandPos(Window& window, Snake& snake, Entity& apple) {
		srand(time(0) + rand()); // updates seed using current time

		do {
			bool unpassed = false;

			//Set random position
			apple.setX(rand() % window.getRows());
			apple.setY(rand() % window.getCols());

			for (Entity& s : snake.getSquares()) {
				if (s.getX() == apple.getX() && s.getY() == apple.getY()) {
					unpassed = true;
					break;
				}
			}
			if (!unpassed) break;
		} while (true);
	}

	inline bool checkSnakeAppleCollision(Snake& snake, Entity& apple) {
		return snake.getX() == apple.getX() && snake.getY() == apple.getY();
	}

	bool checkSnakeTailCollision(Snake& snake) {
		Entity* head = snake.getHead();

		for (Entity& s : snake.getSquares()) {
			if (&s == head) continue;
			else if (s == *head) {
				return true;
			}
		}

		return false;
	}

	void populateGrid(std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>& grid) {
		for (int i = 0; i < GRID_SIZE; ++i) {
			for (int j = 0; j < GRID_SIZE; ++j) {
				grid[i][j] = EntityType::NULL_ENTITY;
			}
		}
	}
}