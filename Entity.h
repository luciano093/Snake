#ifndef ENTITY_H
#define ENTITY_H

#include<SDL.h>
#include<array>
#include"Square.h"
#include"Config.h"
#include"EntityType.h"

class Entity {
public:
	Entity() = default;
	Entity(const Entity& other);
	Entity(Entity&& other) noexcept;
	Entity(SDL_Renderer* renderer, std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid, int xCoord, int yCoord, int width, int height, EntityType type, int r, int g, int b);

	bool operator==(const Entity& other);
	Entity& operator=(const Entity& other);
	Entity& operator=(Entity&& other) noexcept;

	SDL_Texture* getTexture() { return square.getTexture(); }
	SDL_Rect& getRect() { return square.getRect(); }
	const EntityType& getEntityType() const { return type; }

	int getX() { return x; }
	int getY() { return y; }
	void setX(int x);
	void setY(int y);

private:
	SDL_Renderer* renderer = nullptr;
	std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid = nullptr;
	Square square;

	EntityType type = EntityType::ENTITY;

	int x = 0, y = 0;
	int w = 0, h = 0;
};

#endif