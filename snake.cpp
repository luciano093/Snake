#include"Snake.h"

Snake::Snake(SDL_Renderer* r, short x, short y, short width, short height) : renderer(r), x(x), y(y), w(width), h(height) {
	squares.push_back(Square(renderer, x, y, w, h, 0, 255, 0));
}

void Snake::move() {
	switch (direction) {
	case Directions::LEFT:
		x -= w;

		shiftBody();
		squares[0].shiftX(-w);

		break;

	case Directions::RIGHT:
		x += w;

		shiftBody();
		squares[0].shiftX(w);

		break;
	case Directions::UP:
		y -= h;

		shiftBody();
		squares[0].shiftY(-h);

		break;
	case Directions::DOWN:
		y += h;

		shiftBody();
		squares[0].shiftY(h);

		break;
	}
}

// shifts snake parts to the position of the next part except for the head
void Snake::shiftBody() {
	for (auto i = squares.rbegin(); i != squares.rend() - 1; ++i) {
		i->setX((i + 1)->getX());
		i->setY((i + 1)->getY());
	}
}

void Snake::grow() {
	squares.push_back(Square(renderer, squares[squares.size() - 1].getX(), squares[squares.size() - 1].getY(), w, h, r, g, b));

	// pretty colors for snake
	if (r != 255 && g == 255 && b == 0) r += 5;
	else if (r == 255 && g <= 255 && g > 0 && b == 0) g -= 5;
	else if (r == 255 && g == 0 && b != 255) b += 5;
	else if (r <= 255 && r > 0 && g == 0 && b == 255) r -= 5;
	else if (r == 0 && g != 255 && b == 255) g += 5;
	else if (r == 0 && g == 255 && b <= 255 && b > 0) b -= 5;
}