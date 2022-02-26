#include"Entity.h"

Entity::Entity(const Entity& other)
	: renderer(other.renderer), grid(other.grid), square(other.square), type(other.type), x(other.x), y(other.y), w(other.w), h(other.h) { }

Entity::Entity(Entity&& other) noexcept
	: renderer(std::move(other.renderer)), grid(std::move(other.grid)), square(std::move(other.square)), type(std::move(other.type)),
	x(std::exchange(other.x, 0)), y(std::exchange(other.y, 0)), w(std::exchange(other.w, 0)), h(std::exchange(other.h, 0)) { }

Entity::Entity(SDL_Renderer* renderer, std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid, int xCoord, int yCoord, int width, int height, EntityType type, int r, int g, int b) : renderer(renderer), grid(grid), x(xCoord), y(yCoord), w(width), h(height), type(type) {
	square = Square(renderer, x * w, y * h, w, h, r, g, b);
	(*grid)[y][x] = type;
}

bool Entity::operator==(const Entity& other) {
	if (this == &other) return true;

	return type == other.type && x == other.x && y == other.y && w == other.w && h == other.h;
}

Entity& Entity::operator=(const Entity& other) {
	if (this == &other) return *this;

	renderer = other.renderer;
	grid = other.grid;
	square = other.square;
	type = other.type;
	x = other.x;
	y = other.y;
	w = other.w;
	h = other.h;

	return *this;
}

Entity& Entity::operator=(Entity&& other) noexcept {
	std::swap(renderer, other.renderer);
	std::swap(grid, other.grid);
	std::swap(square, other.square);
	std::swap(type, other.type);
	std::swap(x, other.x);
	std::swap(y, other.y);
	std::swap(w, other.w);
	std::swap(h, other.h);

	return *this;
}

void Entity::setX(int newX) {
	(*grid)[y][x] = EntityType::NULL_ENTITY;
	(*grid)[y][newX] = type;

	x = newX;
	square.setX(x * w);
}

void Entity::setY(int newY) {
	(*grid)[y][x] = EntityType::NULL_ENTITY;
	(*grid)[newY][x] = type;

	y = newY;
	square.setY(y * h);
}