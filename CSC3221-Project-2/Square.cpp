#include "Shape.h"
#include "Square.h"
#include "Collision.h"
#include <iostream>

Square::Square(int length) : Square(length, 0, 0) {}

Square::Square(int length, int x, int y) {
	this->length = length;
	this->x = x;
	this->y = y;

	this->type = ShapeTypes::Square;

}

int Square::getLength() const {
	return this->length;
}

/**
 * @brief Uses the appropriate collision algorithm depending on which shape type the Shape is
 * @param rhs
 * @return
*/
bool Square::collidesWith(Shape* rhs) {
	Square* square = this;

	switch (rhs->getShapeName()) {

	case ShapeTypes::Square:
	{
		Square* downCast = static_cast<Square*>(rhs);
		return squareCollision(square, downCast);
	}
	case ShapeTypes::Circle:
	{
		Circle* downCast = static_cast<Circle*>(rhs);
		return squareCircleCollision(square, downCast);
	}

	default:
		return false;
	}

}

ostream& Square::print(ostream& out) const {
	Shape::print(out);
	out << "length=" << length;
	return out;
}

