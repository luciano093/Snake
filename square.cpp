#include"Square.h"

Square::Square() : x(0), y(0), w(0), h(0), rect(SDL_Rect{0, 0, 0, 0}) {

}

Square::Square(SDL_Renderer* rend, short x, short y, short w, short h, uint8_t r, uint8_t g, uint8_t b) : renderer(rend), x(x), y(y), w(w), h(h) {
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	buffer = new uint32_t[unsigned long long(w) * h];

	// fill square with color
	for (size_t pixel = 0; pixel < unsigned long long(w) * h; ++pixel) {
		buffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
	}

	SDL_UpdateTexture(texture, NULL, buffer, w * sizeof(uint32_t));
	rect = { x, y, w, h };

	delete buffer;
}

Square& Square::operator =(const Square& other) {
	if (this == &other) return *this;

	renderer = other.renderer;
	texture = other.texture;
	rect = other.rect;
	x = other.x;
	y = other.y;
	w = other.w;
	h = other.h;

	return *this;
}