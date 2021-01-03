#pragma once
#include <string>
#include <iostream>

using namespace std;

enum class ShapeTypes { Circle, Square };

class Shape {

public:

	// For 3d Support simply change Circle, Square to Sphere + Cube
	// Add getZ and setZ

	/**
	 * @brief Returns the x component of the coordinate
	*/
	int getX() const;

	/**
	 * @brief Returns the x component of the coordinate
	*/
	int getY() const;

	/**
	 * @brief Sets x, given x
	*/
	void setX(int x);

	/**
	 * @brief Sets y given y
	*/
	void setY(int y);

	/**
	 * @brief Translates the shapes x, y
	*/
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
	int x, y; // add z for 3

	ShapeTypes type;

};




