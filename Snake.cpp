#include"Snake.h"

Snake::Snake(const int x, const int y, const int w, const int h) : x(x), y(y), w(w), h(h) {
	parts.push_back(new Square(Main::window.getRenderer(), x, y, w, h, SDL_Color{0, 255, 0}));
}

void Snake::move() {
	if (direction == Direction::NONE) return;

	switch (direction) {
	case Direction::UP:
		y -= h;
		parts.push_front(new Square(Main::window.getRenderer(), x, y, w, h, SDL_Color{ 0, 255, 0 }));
		break;
	case Direction::DOWN:
		y += h;
		parts.push_front(new Square(Main::window.getRenderer(), x, y, w, h, SDL_Color{ 0, 255, 0 }));
		break;
	case Direction::LEFT:
		x -= w;
		parts.push_front(new Square(Main::window.getRenderer(), x, y, w, h, SDL_Color{ 0, 255, 0 }));
		break;
	case Direction::RIGHT:
		x += w;
		parts.push_front(new Square(Main::window.getRenderer(), x, y, w, h, SDL_Color{ 0, 255, 0 }));
		break;
	}

	// delete last element before pop_back
	delete parts.back();
	parts.pop_back();
}

void Snake::grow() {
	parts.push_back(new Square(Main::window.getRenderer(), x, y, w, h, SDL_Color{ 0, 255, 0 }));
}

void Snake::reset(const int newX, const int newY) {
	for (auto i = parts.begin(); i != parts.end(); ++i) {
		delete* i;
	}
	parts.clear();

	x = newX;
	y = newY;

	parts.push_front(new Square(Main::window.getRenderer(), x, y, w, h, SDL_Color{ 0, 255, 0 }));
	direction = Direction::NONE;
}