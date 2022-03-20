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

	void changeBackgroundColor(const SDL_Color& color);

	void createGrid(const int& row_n, const int& col_n);

	int getGridSize() const { return gridSize; };

	int getWidth() const { return w; }
	int getHeight() const { return h; }

	int getRows() const { return rows; }
	int getCols() const { return cols; }

	SDL_Renderer* getRenderer() { return renderer; };

	void drawTextures(const std::vector<SDL_Texture*>& textures, const std::vector<SDL_Rect>& rects);
	void drawTexture(SDL_Texture* const texture, const SDL_Rect& rect);

private:
	unsigned int w, h;
	unsigned int rows = 0, cols = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Grid
	int gridSize = 0;
	SDL_Texture* grid = nullptr;
	SDL_Texture* background = nullptr;

	void createBackground();

	void presentGrid() { SDL_RenderCopy(renderer, grid, NULL, NULL); };
	void presentBackground() { SDL_RenderCopy(renderer, background, NULL, NULL); };
};

inline void Window::clear() {
	SDL_RenderClear(renderer);
	presentBackground();
}

inline void Window::present() {
	if (grid) presentGrid();
	SDL_RenderPresent(renderer);
}

#endif