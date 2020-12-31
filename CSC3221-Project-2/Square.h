#pragma once

#include "Shape.h"

using namespace std;

class Square : public Shape {

public:

	Square(int length);

	Square(int length, int x, int y);

	/**
	 * @brief Returns the length of the square
	 * @return length of the square
	*/
	int getLength() const;

	bool collidesWith(Shape* rhs);

	virtual ostream& print(ostream& out) const override;

private:

	/**
	 * @brief Height and Width of the square
	*/
	int length;

};


