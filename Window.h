#ifndef WINDOW_H
#define WINDOW_H

#include<SDL.h>
#include<iostream>
#include<string>
#include<vector>

class Window {
public:
	Window(const char* title, short width, short height);
	~Window();

	inline void clear();
	inline void present();

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