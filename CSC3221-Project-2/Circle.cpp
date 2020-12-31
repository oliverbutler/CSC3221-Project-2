#include "Circle.h"
#include "Shape.h"
#include "Collision.h"
#include <iostream>

// Equivalent to Square::Square(int height, int width) : Shape() {

Circle::Circle(int radius) : Circle(radius, 0, 0) {}

Circle::Circle(int radius, int x, int y) {
	this->radius = radius;
	this->x = x;
	this->y = y;

	this->type = ShapeTypes::Circle;
}

int Circle::getRadius() const {
	return this->radius;
}

/**
 * @brief Uses the appropriate collision algorithm depending on which shape type the Shape is
 * @param rhs
 * @return
*/
bool Circle::collidesWith(Shape* rhs) {
	Circle* circle = this;

	switch (rhs->getShapeName()) {

	case ShapeTypes::Square:
	{
		Square* downCast = static_cast<Square*>(rhs);
		return squareCircleCollision(downCast, circle);
	}

	case ShapeTypes::Circle:
	{
		Circle* downCast = static_cast<Circle*>(rhs);
		return circleCollision(downCast, circle);
	}

	default:
		return false;
	}

}

ostream& Circle::print(ostream& out) const {
	Shape::print(out);
	out << "radius=" << radius;
	return out;
}
