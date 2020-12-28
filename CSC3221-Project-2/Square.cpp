#include "Shape.h"
#include "Square.h"

// Equivalent to Square::Square(int height, int width) : Shape() {

Square::Square(int height, int width) {
	this->height = height;
	this->width = width;
}

Square::Square(int height, int width, int x, int y) : Shape(x, y) {
	this->height = height;
	this->width = width;
}

int Square::getHeight() const {
	return this->height;
}

int Square::getWidth() const {
	return this->width;
}
