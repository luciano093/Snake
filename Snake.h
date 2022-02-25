#ifndef SNAKE_H
#define SNAKE_H

#include<SDL.h>
#include<vector>
#include"Square.h"

class Snake {
public:
	short x, y;

	enum class Directions { UP, DOWN, LEFT, RIGHT, NONE };

	Snake() = default;
	Snake(SDL_Renderer* renderer, short x, short y, short width, short height);

	inline std::vector<SDL_Texture*>& getTextures();
	inline std::vector<SDL_Rect>& getRects();
	inline std::vector<Square>& getSquares() { return squares; }

	void setSize(const short newSize) { squares.resize(newSize, squares[0]); }

	short getWidth() const { return w; }
	short getHeight() const { return h; }

	void goLeft() { direction = Directions::LEFT; };
	void goRight() { direction = Directions::RIGHT; };
	void goUp() { direction = Directions::UP; };
	void goDown() { direction = Directions::DOWN; };

	Directions getDirection() const { return direction; }
	size_t getSize() const { return squares.size(); }
	Square* getHead() { return &squares[0]; }
	Square* getTail() { return &squares[squares.size() - 1]; }

	void move();
	void grow();

private:
	Directions direction = Directions::NONE;

	short w, h;
	
	std::vector<Square> squares;
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> rects;

	SDL_Renderer* renderer = nullptr;

	uint8_t r = 0, g = 255, b = 0;

	void shiftBody();
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
