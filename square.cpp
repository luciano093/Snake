#include"Square.h"

Square::Square() : x(0), y(0), w(0), h(0), rect(SDL_Rect{0, 0, 0, 0}) {

}

Square::Square(SDL_Renderer* rend, short x, short y, short w, short h, uint8_t r, uint8_t g, uint8_t b) : renderer(rend), x(x), y(y), w(w), h(h) {
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	uint32_t* buffer = new uint32_t[uint64_t(w) * h];

	// fill square with color
	for (size_t pixel = 0; pixel < unsigned long long(w) * h; ++pixel) {
		buffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
	}

	SDL_UpdateTexture(texture, NULL, buffer, w * sizeof(uint32_t));
	rect = { x, y, w, h };

	delete[] buffer;
}