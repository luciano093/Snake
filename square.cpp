#include"Square.h"

Square::Square() : x(0), y(0), w(0), h(0), rect(SDL_Rect{0, 0, 0, 0}) {

}

Square::Square(SDL_Renderer* const renderer, const int x, const int y, const int w, const int h, const SDL_Color color) : x(x), y(y), w(w), h(h) {
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, w, h);

	uint32_t* buffer = new uint32_t[uint64_t(w) * h];

	// fill square with color
	for (size_t pixel = 0; pixel < unsigned long long(w) * h; ++pixel) {
		buffer[pixel] = (0xff << 24) | (color.r << 16) | (color.g << 8) | color.b;
	}

	SDL_UpdateTexture(texture, NULL, buffer, w * sizeof(uint32_t));
	rect = { x, y, w, h };

	delete[] buffer;
}


Square::~Square() { SDL_DestroyTexture(texture); }