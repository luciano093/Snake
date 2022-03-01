#include"Game.h"

namespace Game {
	Window window("Snake", 500, 500);
	Snake snake;
	Entity apple;

	array2d grid;

	bool running = true;
	int delay = 100;

	int collision_number = 0;
	unsigned int score = 0;

	SDL_Event event;

	Layer hiddenLayer;
	Layer output;
	vector2d predicted;

	SDL_Event left, right, up, down;
	int maxSteps = 50;
	int currentMaxSteps = maxSteps;
	int currentSteps = 0;
	int totalSteps = 0;

	int maxSnakesPerGen = 500;
	int currentSnakes = 1;

	vector2d input;
	vector2d hloutput;

	int gen = 1;

	void start() {
		window.createGrid(GRID_SIZE, GRID_SIZE);

		populateGrid(grid);

		snake = Snake(window.getRenderer(), &grid, GRID_SIZE/2, GRID_SIZE/2, window.getGridSize(), window.getGridSize());
		apple = Entity(window.getRenderer(), &grid, GRID_SIZE - 1, GRID_SIZE - 1, window.getGridSize(), window.getGridSize(), EntityType::FOOD, 255, 0, 0);

		input = { {(double)snake.getDirection(), (double)snake.getX(), (double)snake.getY(), (double)apple.getX(), (double)apple.getY()} };

		hiddenLayer = Layer(5, 7);
		hloutput = activationReLu(hiddenLayer.forward(input));

		output = Layer(7, 4);
		predicted = activationSoftmax(output.forward(hloutput));

		right.type = SDL_KEYDOWN;
		right.key.keysym.sym = SDLK_RIGHT;

		left.type = SDL_KEYDOWN;
		left.key.keysym.sym = SDLK_LEFT;

		up.type = SDL_KEYDOWN;
		up.key.keysym.sym = SDLK_UP;

		down.type = SDL_KEYDOWN;
		down.key.keysym.sym = SDLK_DOWN;

		grid[apple.getY()][apple.getX()] = apple.getEntityType();
	}

	void update() {
		if (currentSnakes >= maxSnakesPerGen) {
			currentSnakes = 0;

			Ai::adjustLayers(hiddenLayer, output);
			std::cout << "generation: " << ++gen << " best fitness: " << Ai::bestFitness << "\n";
		}
		else {
			hiddenLayer.adjustWeights();
			hiddenLayer.adjustBiases();
			output.adjustWeights();
			output.adjustBiases();
		}

		++currentSteps;
		++totalSteps;

		input = { {(double)snake.getDirection(), (double)snake.getX(), (double)snake.getY(), (double)apple.getX(), (double)apple.getY()} };
		hloutput = activationReLu(hiddenLayer.forward(input));
		predicted = activationSoftmax(output.forward(hloutput));

		if (predicted[0][0] >= predicted[0][1] && predicted[0][0] >= predicted[0][2] && predicted[0][0] >= predicted[0][3]) {
			SDL_PushEvent(&left);
		}
		else if (predicted[0][1] >= predicted[0][0] && predicted[0][1] >= predicted[0][2] && predicted[0][1] >= predicted[0][3]) {
			SDL_PushEvent(&right);
		}
		else if (predicted[0][2] >= predicted[0][0] && predicted[0][2] >= predicted[0][1] && predicted[0][2] >= predicted[0][3]) {
			SDL_PushEvent(&up);
		}
		else if (predicted[0][3] >= predicted[0][0] && predicted[0][3] >= predicted[0][1] && predicted[0][3] >= predicted[0][2]) {
			SDL_PushEvent(&down);
		}

		// movement
		if (snake.getDirection() != Snake::Direction::NONE && !isOutOfScreen(grid, snake)) {
			snake.move();
		}
		else if (isOutOfScreen(grid, snake)) {
			handleSnakeDeath();
		}
		
		// check snake collision with food
		if (snake.hasEatenFood()) {
			maxSteps += maxSteps;
			std::cout << "score: " << ++score << std::endl;
			snake.grow();
			giveAppleRandPos(window, snake, apple);
		}

		// collision with tail
		if ((snake.getSize() > 3 && checkSnakeTailCollision(snake)) || currentSteps >= maxSteps) {
			handleSnakeDeath();
		}

		window.updateTextures(snake.getTextures(), snake.getRects());
		window.updateTexture(apple.getTexture(), apple.getRect());
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

	bool isOutOfScreen(array2d& grid, Snake& snake) {
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

	void handleOutOfScreen(array2d& grid, Snake& snake) {
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

	bool checkSnakeTailCollision(Snake& snake) {
		Entity* head = snake.getHead();

		for (Entity& s : snake.getSquares()) {
			if (&s == head) continue;
			else if (head->getX() == s.getX() && head->getY() == s.getY()) {
				return true;
			}
		}

		return false;
	}

	void populateGrid(array2d& grid) {
		for (int i = 0; i < GRID_SIZE; ++i) {
			for (int j = 0; j < GRID_SIZE; ++j) {
				grid[i][j] = EntityType::NULL_ENTITY;
			}
		}
	}

	void handleSnakeDeath() {
		maxSteps = currentMaxSteps;
		++currentSnakes;
		Ai::snakes.push_back({ {hiddenLayer, output}, Ai::calcFitness(currentSteps, score) });

		// Code to kill
		snake.setSize(1);
		snake.setX(GRID_SIZE / 2);
		snake.setY(GRID_SIZE / 2);
		currentSteps = 0;
		score = 0;
	}
}