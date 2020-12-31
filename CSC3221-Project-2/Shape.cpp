#include "Shape.h"
#include <iostream>

using namespace std;


int Shape::getX() const {
	return this->x;
}

int Shape::getY() const {
	return this->y;
}

void Shape::translate(int x, int y) {
	this->x += x;
	this->y += y;
}

ShapeTypes Shape::getShapeName() const {
	return this->type;
}


ostream& operator<<(ostream& out, const Shape& s) {
	// Put the printing on this print() function, this CAN be virtualized so 
	// solves the problem of printing a base* shape = new Square() problem
	return s.print(out);
}

ostream& Shape::print(ostream& out) const {

	string name;

	if (type == ShapeTypes::Circle) name = "CIRCLE";
	else if (type == ShapeTypes::Square) name = "SQUARE";

	out << "[" << name << "] (" << x << ", " << y << ") ";
	return out;
}