#ifndef WINDOW_H
#define WINDOW_H

#include<SDL.h>
#include<iostream>
#include<string>
#include<vector>

class Window {
public:
	Window(const char* title, short width, short height);

	inline void clear();
	inline void present();
	inline void quit();

	void createGrid(const short rows, const short cols);
	inline void presentGrid();
	inline short getGridSize() const { return gridSize; };

	inline short getWidth() const { return w; }
	inline short getHeight() const { return h; }

	inline short getRows() const { return rows; }
	inline short getCols() const { return cols; }

	inline SDL_Renderer* getRenderer() { return renderer; };

	void updateTextures(std::vector<SDL_Texture*>& textures, std::vector<SDL_Rect>& rects);
	void updateTexture(SDL_Texture* texture, SDL_Rect& rect);

private:
	short w, h;
	short rows = 0, cols = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Grid
	short gridSize = 0;
	SDL_Texture* grid = nullptr;
	uint32_t* gridBuffer = nullptr;
};

Window::Window(const char* title, short width, short height) : w(width), h(height) {
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_HIDDEN);
	if (!window) std::cerr << "Failed to create SDL_Window!" << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if(!renderer) std::cerr << "Failed to create SDL_Renderer!" << SDL_GetError() << std::endl;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_ShowWindow(window);
}

inline void Window::clear() {
	SDL_RenderClear(renderer);
}

inline void Window::present() {
	SDL_RenderPresent(renderer);
}

inline void Window::presentGrid() {
	if (grid)
		SDL_RenderCopy(renderer, grid, NULL, NULL);
}

inline void Window::quit() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Window::createGrid(short row_n, short col_n) {
	rows = row_n;
	cols = col_n;

	gridSize = h / rows; // no idea if this might give errors

	grid = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	gridBuffer = new uint32_t[unsigned long long(w) * h];

	// gray color
	uint32_t r = 110;
	uint32_t b = 110;
	uint32_t g = 110;

	// draw initial background color
	for (int pixel = 0; pixel < w * h; ++pixel) {
		gridBuffer[pixel] = (0xff << 24) | (0xff << 16) | (0xff << 8) | 0xff;
	}

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
}

void Window::updateTextures(std::vector<SDL_Texture*>& textures, std::vector<SDL_Rect>& rects) {
	for (size_t i = 0; i < textures.size(); ++i) {
		SDL_RenderCopy(renderer, textures[i], NULL, &rects[i]);
	}
}

void Window::updateTexture(SDL_Texture* texture, SDL_Rect& rect) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

#endif