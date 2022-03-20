#ifndef SNAKE_H
#define SNAKE_H

#include"Config.h"
#include"Main.h"
#include"Window.h"
#include"Square.h"
#include<list>

class Snake {
public:
	enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

	Direction direction = Direction::NONE;

	Snake(const int x, const int y, const int w, const int h);

	const std::list<Square*>& getParts() const { return parts; }
	const int getX() const { return x; }
	const int getY() const { return y; }
	const Square* const getHead() const { return parts.front(); }

	void move();
	void grow();
	void reset(const int x, const int y);

private:
	std::list<Square*> parts;

	int x, y;
	int w, h;
};


#endif