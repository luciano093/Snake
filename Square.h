#ifndef SQUARE_H
#define SQUARE_H

#include<iostream>

#pragma warning(push, 0)
#include<SDL.h>
#pragma warning(pop)

class Square {
public:
	Square();
	Square(SDL_Renderer* renderer, const int x, const int y, const int w, const int h, const uint8_t r = 0, const uint8_t g = 0, const uint8_t b = 0);

	SDL_Texture* const getTexture() { return texture; };
	SDL_Rect& getRect() { return rect; }

	int const getX() const { return x; };
	int const getY() const { return y; };
	int const getW() const { return w; };
	int const getH() const { return h; };

	void shiftX(const int newX) { x += newX; rect.x += newX; };
	void shiftY(const int newY) { y += newY; rect.y += newY; };
	void setX(const int newX) { x = newX; rect.x = newX; };
	void setY(const int newY) { y = newY; rect.y = newY; };

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	int x, y;
	int w, h;
};
#endif
