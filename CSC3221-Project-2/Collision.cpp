#include "Collision.h"

// This is sadly psuedo random, however it suits our purposes :)
int genRand(int min, int max) {
	return rand() % (max - min + 1) + min;
}

bool squareCollision(Square* lhs, Square* rhs) {

	// This if statement can be increased to support x,y, AND z axes to work in 3D

	// basic idea of a square collision is if a rectangle of area of >= 0 exists between the rectangles then they overlap

	if (lhs->getX() + lhs->getLength() >= rhs->getX() && // lhs right edge is past rhs left
		lhs->getX() <= rhs->getX() + rhs->getLength() && // lhs left edge is past rhs right
		lhs->getY() + lhs->getLength() >= rhs->getY() && // lhs top edge is past rhs bottom
		lhs->getY() <= rhs->getY() + rhs->getLength()) { // lhs bottom edge is past rhs top 
		return true;
	} else {
		return false;
	}

}

bool circleCollision(Circle* lhs, Circle* rhs) {

	// Can be upgraded to work with Spheres, using 3d pythagoras

	// Circle collision is nice and easy, if their two centers are further away than their combined radii then they dont touch

	int distX = lhs->getX() - rhs->getX(); // Distance on x axis
	int distY = lhs->getY() - rhs->getY(); // Distance on y axis
	float distance = sqrt(distX * distX + distY * distY); // Total distance from center to center

	if (distance <= lhs->getRadius() + rhs->getRadius()) { // If the distance is MORE than both of the radii, then they don't touch.
		return true;
	} else {
		return false;
	}
}

bool squareCircleCollision(Square* s, Circle* c) {

	// Similar logic can be used to make this 3D, using 3d pythagoras and comparing against the nearest face

	// This algorithm will first locate the edge of the square nearest to the circle

	int closestX = c->getX();
	int closestY = c->getY();

	// Which edge is closest to the circle?


	if (c->getX() < s->getX()) { // left edge
		closestX = s->getX();
	} else if (c->getX() > s->getX() + s->getLength()) { // Right edge
		closestX = s->getX() + s->getLength();
	}

	if (c->getY() < s->getY()) { // top edge
		closestY = s->getY();
	} else if (c->getY() > s->getY() + s->getLength()) {  // bottom edge
		closestY = s->getY() + s->getLength();
	}

	// Same Pythagorean logic used in the circle collision algorithm

	float distX = c->getX() - closestX;
	float distY = c->getY() - closestY;

	// If the distance is less than the collision we have ourselves a collision!
	float distance = sqrt(distX * distX + distY * distY); // Total distance from nearest edge to the circle

	if (distance <= c->getRadius()) {
		return true;
	} else {
		return false;
	}

}
