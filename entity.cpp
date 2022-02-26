#include"Entity.h"

Entity::Entity(SDL_Renderer* renderer, std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid, int xCoord, int yCoord, int width, int height) : renderer(renderer), grid(grid), x(xCoord), y(yCoord), w(width), h(height) {
	square = Square(renderer, x * w, y * h, w, h);
	(*grid)[y][x] = type;
}

Entity::Entity(SDL_Renderer* renderer, std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid, int xCoord, int yCoord, int width, int height, EntityType type, int r, int g, int b) : renderer(renderer), grid(grid), x(xCoord), y(yCoord), w(width), h(height), type(type) {
	square = Square(renderer, x * w, y * h, w, h, r, g, b);
	(*grid)[y][x] = type;
}

bool Entity::operator==(const Entity& other) {
	if (this == &other) return true;

	return type == other.type && x == other.x && y == other.y && w == other.w && h == other.h;
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