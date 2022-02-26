#include"Snake.h"

Snake::Snake(SDL_Renderer* r, std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid, short x, short y, short width, short height) : renderer(r), grid(grid), x(x), y(y), w(width), h(height) {
	squares.push_back(Entity(renderer, grid, x, y, w, h, EntityType::ENTITY, 0, 255, 0));

	(*grid)[y][x] = EntityType::ENTITY;
}

Snake& Snake::operator =(const Snake& other) {
	if (this == &other) return *this;

	grid = other.grid;

	x = other.x;
	y = other.y;
	w = other.w;
	h = other.h;
	squares = other.squares;
	textures = other.textures;
	rects = other.rects;
	renderer = other.renderer;
	r = other.r;
	g = other.g;
	b = other.b;

	return *this;
}

void Snake::setX(short newX) {
	if ((*grid)[y][newX] == EntityType::FOOD) std::cout << "Food eaten!" << std::endl;

	(*grid)[y][newX] = EntityType::ENTITY;

	x = newX;
	squares[0].setX(x);
}

void Snake::setY(short newY) {
	if ((*grid)[newY][x] == EntityType::FOOD) std::cout << "Food eaten!" << std::endl;

	(*grid)[newY][x] = EntityType::ENTITY;

	y = newY;
	squares[0].setY(y);
}

void Snake::move() {
	switch (direction) {
	case Direction::LEFT:
		shiftBody();
		setX(--x);

		break;
	case Direction::RIGHT:
		shiftBody();
		setX(++x);

		break;
	case Direction::UP:
		shiftBody();
		setY(--y);

		break;
	case Direction::DOWN:
		shiftBody();
		setY(++y);

		break;
	}
}

void Snake::moveTo(unsigned int newX, unsigned int newY) {
	shiftBody();
	setX(newX);
	setY(newY);
}

// shifts snake parts to the position of the next part except for the head
void Snake::shiftBody() {
	for (auto square = squares.rbegin(); square != squares.rend() - 1; ++square) {
		square->setX((square + 1)->getX());
		square->setY((square + 1)->getY());
	}

	(*grid)[squares[squares.size() - 1].getY()][squares[squares.size() - 1].getX()] = EntityType::NULL_ENTITY;
}

void Snake::grow() {
	squares.push_back(Entity(renderer, grid, squares[squares.size() - 1].getX(), squares[squares.size() - 1].getY(), w, h, EntityType::ENTITY, r, g, b));

	// pretty colors for snake
	if (r != 255 && g == 255 && b == 0) r += 5;
	else if (r == 255 && g <= 255 && g > 0 && b == 0) g -= 5;
	else if (r == 255 && g == 0 && b != 255) b += 5;
	else if (r <= 255 && r > 0 && g == 0 && b == 255) r -= 5;
	else if (r == 0 && g != 255 && b == 255) g += 5;
	else if (r == 0 && g == 255 && b <= 255 && b > 0) b -= 5;
}