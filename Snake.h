#ifndef SNAKE_H
#define SNAKE_H

#include<SDL.h>
#include<vector>
#include<array>
#include<iostream>
#include"Square.h"
#include"Config.h"
#include"Entity.h"

class Snake {
public:
	enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

	Snake() = default;
	Snake(SDL_Renderer* renderer, std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid, short x, short y, short width, short height);

	Snake& operator =(const Snake& other);

	inline std::vector<SDL_Texture*>& getTextures();
	inline std::vector<SDL_Rect>& getRects();
	std::vector<Entity>& getSquares() { return squares; }

	void setSize(const short newSize) { squares.resize(newSize, squares[0]); }

	short getX() const { return x; }
	short getY() const { return y; }

	short getWidth() const { return w; }
	short getHeight() const { return h; }

	void goLeft() { direction = Direction::LEFT; };
	void goRight() { direction = Direction::RIGHT; };
	void goUp() { direction = Direction::UP; };
	void goDown() { direction = Direction::DOWN; };

	Direction getDirection() const { return direction; }
	size_t getSize() const { return squares.size(); }
	Entity* getHead() { return &squares[0]; }
	Entity* getTail() { return &squares[squares.size() - 1]; }

	void move();
	void moveTo(unsigned int x, unsigned int y);
	void grow();

private:
	std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE>* grid;

	Direction direction = Direction::NONE;

	short x, y;
	short w, h;
	
	std::vector<Entity> squares;
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> rects;

	SDL_Renderer* renderer = nullptr;

	uint8_t r = 0, g = 255, b = 0;

	void shiftBody();
	void setX(short x);
	void setY(short y);
};

inline std::vector<SDL_Texture*>& Snake::getTextures() {
	textures.clear();
	for (auto s = squares.rbegin(); s != squares.rend(); ++s) {
		textures.push_back(s->getTexture());
	}

	return textures;
}

inline std::vector<SDL_Rect>& Snake::getRects() {
	rects.clear();
	for (auto s = squares.rbegin(); s != squares.rend(); ++s) {
	rects.push_back(s->getRect());
	}

	return rects;
}
#endif
