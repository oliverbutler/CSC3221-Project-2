#pragma once

#include "Shape.h"

class Circle : public Shape {

public:

	Circle(int radius);

	Circle(int length, int x, int y);

	/**
	 * @brief Returns the length of the square
	 * @return length of the square
	*/
	int getRadius() const;

	bool collidesWith(Shape* rhs);

	virtual ostream& print(ostream& out) const override;

private:

	/**
	 * @brief Height and Width of the square
	*/
	int radius;

};

