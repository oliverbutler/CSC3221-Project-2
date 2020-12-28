#pragma once

#include "Shape.h"

class Square : public Shape {

public:

	Square(int height, int width);

	Square(int height, int width, int x, int y);

	/**
	 * @brief Returns the height of the square
	 * @return height of square
	*/
	int getHeight() const;

	/**
	 * @brief Returns the width of the square
	 * @return width of the square
	*/
	int getWidth() const;

private:

	/**
	 * @brief Height and Width of the square
	*/
	int height, width;

};

