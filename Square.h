#ifndef SQUARE_H
#define SQUARE_H

#include<iostream>

#pragma warning(push, 0)
#include<SDL.h>
#pragma warning(pop)

class Square {
public:
	Square();
	Square(SDL_Renderer* renderer, short x, short y, short w, short h, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);

	SDL_Texture* getTexture() { return texture; };
	SDL_Rect& getRect() { return rect; }

	short getX() { return x; };
	short getY() { return y; };
	short getW() { return w; };
	short getH() { return h; };

	void shiftX(const int newX) { x += newX; rect.x += newX; };
	void shiftY(const int newY) { y += newY; rect.y += newY; };
	void setX(const int newX) { x = newX; rect.x = newX; };
	void setY(const int newY) { y = newY; rect.y = newY; };

	bool operator==(const Square& other) {
		if (this == &other) return true;

		return this->x == other.x && this->y == other.y && this->w == other.w && this->h == other.h;
	}

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;
	uint32_t* buffer = nullptr;

	short x, y;
	short w, h;
};

#endif
