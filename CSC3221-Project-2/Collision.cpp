#include "Collision.h"

bool squareCollision(Square* lhs, Square* rhs) {

	// basic idea of a square collision is if a rectangle of area of >= 0 exists between the rectangles then they overlap

	if (lhs->getX() + lhs->getLength() >= rhs->getX() &&
		lhs->getX() <= rhs->getX() + rhs->getLength() &&
		lhs->getX() + lhs->getLength() >= rhs->getY() &&
		lhs->getY() <= rhs->getY() + rhs->getLength()) {
		return true;
	} else {
		return false;
	}

}

bool circleCollision(Circle* lhs, Circle* rhs) {
	float distX = lhs->getX() - rhs->getX(); // Distance on x axis
	float distY = lhs->getY() - rhs->getY(); // Distance on y axis
	float distance = sqrt(distX * distX + distY * distY); // Total distance from center to center

	if (distance <= lhs->getRadius() + rhs->getRadius()) { // If the distance is MORE than both of the radii, then they don't touch.
		return true;
	} else {
		return false;
	}
}

bool squareCircleCollision(Square* s, Circle* c) {

	// This algorithm will first locate the edge of the square nearest to the circle

	float closestX = 0;
	float closestY = 0;

	// Which edge is closest to the circle?

	if (c->getX() < s->getX()) closestX = s->getX(); // left edge
	else if (c->getX() > s->getX() + s->getLength()) closestX = s->getX() + s->getLength(); // Right edge

	if (c->getY() < s->getY()) closestY = s->getY(); // top edge
	else if (c->getY() > s->getY() + s->getLength()) closestY = s->getY() + s->getLength(); // bottom edge

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
