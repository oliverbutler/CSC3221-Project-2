#pragma once
#include <string>
#include <iostream>

using namespace std;

enum class ShapeTypes { Circle, Square };

class Shape {

public:

	/**
	 * @brief Returns the x component of the coordinate
	*/
	int getX() const;

	/**
	 * @brief Returns the x component of the coordinate
	*/
	int getY() const;

	void translate(int x, int y);

	/**
	 * @brief
	*/
	ShapeTypes getShapeName() const;

	virtual bool collidesWith(Shape* rhs) = 0;

	/**
	 * @brief Overloaded operator for <<
	 * @param out
	 * @param s
	 * @return
	*/
	friend ostream& operator<<(ostream& out, const Shape& s);

	virtual ostream& print(ostream& out) const;


protected:


	/**
	 * @brief Coordinates of the object, (bottom left rectangle, center circle)
	*/
	int x, y;

	ShapeTypes type;

};




