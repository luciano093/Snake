#ifndef WINDOW_H
#define WINDOW_H

#include<SDL.h>
#include<iostream>
#include<string>
#include<vector>

class Window {
public:
	Window(const char* title, int width, int height);
	~Window();

	inline void clear();
	inline void present();

	void presentGrid() { SDL_RenderCopy(renderer, grid, NULL, NULL); };
	void presentBackground() { SDL_RenderCopy(renderer, background, NULL, NULL); };

	void createGrid(const int& row_n, const int& col_n);

	int getGridSize() const { return gridSize; };

	int getWidth() const { return w; }
	int getHeight() const { return h; }

	int getRows() const { return rows; }
	int getCols() const { return cols; }

	SDL_Renderer* getRenderer() { return renderer; };

	void updateTextures(const std::vector<SDL_Texture*>& textures, const std::vector<SDL_Rect>& rects);
	void updateTexture(SDL_Texture* const texture, const SDL_Rect& rect);

private:
	unsigned int w, h;
	unsigned int rows = 0, cols = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Grid
	int gridSize = 0;
	SDL_Texture* grid = nullptr;
	SDL_Texture* background = nullptr;
};

inline void Window::clear() {
	SDL_RenderClear(renderer);
	presentBackground();
	if (grid) presentGrid();
}

inline void Window::present() {
	SDL_RenderPresent(renderer);
}

#endif