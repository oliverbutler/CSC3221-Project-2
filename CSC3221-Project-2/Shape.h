#pragma once
class Shape {

public:

	/**
	* @brief Create a shape at (0,0)
	*/
	Shape();

	/**
	 * @brief Create a shape at (x,y)
	 * @param x
	 * @param y
	*/
	Shape(int x, int y);

	/**
	 * @brief Returns the x component of the coordinate
	*/
	int getX() const;

	/**
	 * @brief Returns the x component of the coordinate
	*/
	int getY() const;

protected:

	/**
	 * @brief Coordinates of the object, (bottom left rectangle, center circle)
	*/
	int x, y;

};

