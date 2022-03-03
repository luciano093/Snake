#include"Window.h"

Window::Window(const char* title, int width, int height) : w(width), h(height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) std::cerr << "SDL has failed to initialize video " << SDL_GetError() << "\n";

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_HIDDEN);
	if (!window) std::cerr << "Failed to create SDL_Window!" << SDL_GetError() << "\n";

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer) std::cerr << "Failed to create SDL_Renderer!" << SDL_GetError() << std::endl;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_ShowWindow(window);
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Window::createGrid(const int& row_n, const int& col_n) {
	rows = row_n;
	cols = col_n;

	gridSize = h / rows; // no idea if this might give errors

	grid = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, w, h);

	uint32_t* gridBuffer = new uint32_t[uint32_t(w) * h];

	// gray color
	uint8_t r = 110;
	uint8_t b = 110;
	uint8_t g = 110;

	// draw rows
	for (int row_pos = 0; row_pos < w * h; row_pos += h * (h / rows)) {
		for (int pixel = row_pos; pixel < h + row_pos; ++pixel) {
			gridBuffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
		}
	}
	for (int pixel = w * h - w; pixel < w * h; ++pixel) {
		// draws last row
		gridBuffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
	}

	// draw columns
	for (int pixel = 0; pixel < w * h; pixel += w / cols) {
		gridBuffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
	}
	for (int pixel = w - 1; pixel < w * h; pixel += h) {
		// draws last column
		gridBuffer[pixel] = (0xff << 24) | (r << 16) | (g << 8) | b;
	}

	SDL_UpdateTexture(grid, NULL, gridBuffer, w * sizeof(uint32_t));

	delete[] gridBuffer;
}

void Window::updateTextures(const std::vector<SDL_Texture*>& textures, const std::vector<SDL_Rect>& rects) {
	for (size_t i = 0; i < textures.size(); ++i) {
		SDL_RenderCopy(renderer, textures[i], NULL, &rects[i]);
	}
}

void Window::updateTexture(SDL_Texture* const texture, const SDL_Rect& rect) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}