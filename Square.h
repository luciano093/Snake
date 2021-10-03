#ifndef SQUARE_H
#define SQUARE_H

#include<iostream>
#include<SDL.h>

class Square {
public:
	Square(SDL_Renderer* renderer, short x, short y, short w, short h, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);

	inline SDL_Texture* getTexture() { return texture; };
	inline SDL_Rect& getRect() { return rect; }

	inline short getX() { return x; };
	inline short getY() { return y; };
	inline short getW() { return w; };
	inline short getH() { return h; };

	inline void shiftX(const int newX) { x += newX; rect.x += newX; };
	inline void shiftY(const int newY) { y += newY; rect.y += newY; };
	inline void setX(const int newX) { x = newX; rect.x = newX; };
	inline void setY(const int newY) { y = newY; rect.y = newY; };

	inline bool operator==(const Square& other) {
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

Square::Square(SDL_Renderer* rend, short x, short y, short w, short h, uint8_t r, uint8_t g, uint8_t b) : renderer(rend), x(x), y(y), w(w), h(h){
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	buffer = new uint32_t[unsigned long long(w) * h];

	// fill square with color
	for (size_t pixel = 0; pixel < unsigned long long(w) * h; ++pixel) {
		buffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
	}

	SDL_UpdateTexture(texture, NULL, buffer, w * sizeof(uint32_t));
	rect = { x, y, w, h };
}

#endif
