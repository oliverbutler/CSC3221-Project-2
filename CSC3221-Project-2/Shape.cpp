#include "Shape.h"

Shape::Shape() {
	this->x = 0;
	this->y = 0;
}

Shape::Shape(int x, int y) {
	this->x = x;
	this->y = y;
}

int Shape::getX() const {
	return this->x;
}

int Shape::getY() const {
	return this->y;
}

