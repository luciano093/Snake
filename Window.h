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

	void createGrid(const int& row_n, const int& col_n);
	inline void presentGrid();
	inline int getGridSize() const { return gridSize; };

	inline int getWidth() const { return w; }
	inline int getHeight() const { return h; }

	inline int getRows() const { return rows; }
	inline int getCols() const { return cols; }

	inline SDL_Renderer* getRenderer() { return renderer; };

	void updateTextures(std::vector<SDL_Texture*>& textures, std::vector<SDL_Rect>& rects);
	void updateTexture(SDL_Texture* texture, SDL_Rect& rect);

private:
	unsigned int w, h;
	unsigned int rows = 0, cols = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Grid
	int gridSize = 0;
	SDL_Texture* grid = nullptr;
};

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

#endif