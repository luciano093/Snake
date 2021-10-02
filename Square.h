#ifndef SQUARE_H
#define SQUARE_H

#include<iostream>
#include<SDL.h>

class Square {
public:
	Square(SDL_Renderer* renderer, int x, int y, int w, int h, uint32_t r = 0, uint32_t g = 0, uint32_t b = 0);

	inline SDL_Texture* getTexture() { return texture; };
	inline SDL_Rect getRect() { return rect; }

	inline int getX() { return x; };
	inline int getY() { return y; };
	inline int getW() { return w; };
	inline int getH() { return h; };

	inline void shiftX(int newX) { x += newX; rect.x += newX; };
	inline void shiftY(int newY) { y += newY; rect.y += newY; };
	inline void setX(int newX) { x = newX; rect.x = newX; };
	inline void setY(int newY) { y = newY; rect.y = newY; };
	bool operator==(const Square& other) {
		if (this == &other)
			return true;

		return this->x == other.x && this->y == other.y && this->w == other.w && this->h == other.h;
	}

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;
	uint32_t* buffer = nullptr;

	int x, y;
	int w, h;
};

Square::Square(SDL_Renderer* rend, int x, int y, int w, int h, uint32_t r, uint32_t g, uint32_t b) : renderer(rend), x(x), y(y), w(w), h(h){
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	buffer = new uint32_t[ w * h];

	// fill square with color
	for (size_t pixel = 0; pixel < w * h; ++pixel) {
		buffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
	}

	SDL_UpdateTexture(texture, NULL, buffer, w * sizeof(uint32_t));
	rect = { x, y, w, h };
}

#endif
