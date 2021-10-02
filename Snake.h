#ifndef SNAKE_H
#define SNAKE_H

#include<SDL.h>
#include<vector>
#include"Square.h"

enum class Directions { UP, DOWN, LEFT, RIGHT, NONE };

class Snake {
public:
	Snake(SDL_Renderer* renderer, int x, int y, int width, int height);

	inline std::vector<SDL_Texture*> getTextures();
	inline std::vector<SDL_Rect> getRects();
	inline std::vector<Square>& getSquares() { return squares; }

	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void setX(int newX);
	inline void setY(int newY);

	inline void setSize(int newSize) { squares.resize(1, squares[0]); }

	inline int getWidth() { return w; }
	inline int getHeight() { return h; }

	inline void goLeft();
	inline void goRight();
	inline void goUp();
	inline void goDown();

	inline Directions getDirection() { return direction; }
	inline int getSize() { return squares.size(); }
	inline Square* getHead() { return &squares[0]; }

	void move();
	void grow();

private:
	Directions direction = Directions::NONE;

	int w, h;
	int x, y;
	
	std::vector<Square> squares;
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> rects;

	SDL_Renderer* renderer = nullptr;

	void shiftBody();

	uint8_t r = 0, g = 255, b = 0;
};

Snake::Snake(SDL_Renderer* r, int x, int y, int width, int height) : renderer(r), x(x), y(y), w(width), h(height) {
	squares.push_back(Square(renderer, x, y, w, h, 0, 255, 0));
}

inline std::vector<SDL_Texture*> Snake::getTextures() {
	textures.clear();
	for (auto s = squares.rbegin(); s != squares.rend(); ++s) {
		textures.push_back(s->getTexture());
	}

	return textures;
}

inline std::vector<SDL_Rect> Snake::getRects() {
	rects.clear();
	for (auto s = squares.rbegin(); s != squares.rend(); ++s) {
	rects.push_back(s->getRect());
	}

	return rects;
}

inline void Snake::goLeft() {
	direction = Directions::LEFT;
}

inline void Snake::goRight() {
	direction = Directions::RIGHT;
}

inline void Snake::goUp() {
	direction = Directions::UP;
}

inline void Snake::goDown() {
	direction = Directions::DOWN;
}

void Snake::move() {
	switch (direction) {
	case Directions::LEFT:
		x -= w;

		shiftBody();
		squares[0].shiftX(-w);

		break;

	case Directions::RIGHT:
		x += w;

		shiftBody();
		squares[0].shiftX(w);

		break;
	case Directions::UP:
		y -= h;

		shiftBody();
		squares[0].shiftY(-h);

		break;
	case Directions::DOWN:
		y += h;

		shiftBody();
		squares[0].shiftY(h);

		break;
	}
}


// shifts snake parts to the position of the next part except for the head
void Snake::shiftBody() {
	for (auto i = squares.rbegin(); i != squares.rend() - 1; ++i) {
		i->setX((i + 1)->getX());
		i->setY((i + 1)->getY());
	}
}

void Snake::grow() {
	squares.push_back(Square(renderer, squares[squares.size() - 1].getX(), squares[squares.size() - 1].getY(), w, h, r, g, b));

	if (r != 255 && g == 255 && b == 0) r += 5;
	else if (r == 255 && g <= 255 && g > 0 && b == 0) g -= 5;
	else if (r == 255 && g == 0 && b != 255) b += 5;
	else if (r <= 255 && r > 0 && g == 0 && b == 255) r -= 5;
	else if (r == 0 && g != 255 && b == 255) g += 5;
	else if (r == 0 && g == 255 && b <= 255 && b > 0) b -= 5;
}

inline void Snake::setX(int newX) {
	x = newX;
	squares[0].setX(x);
}

inline void Snake::setY(int newY) {
	y = newY;
	squares[0].setY(y);
}

#endif
