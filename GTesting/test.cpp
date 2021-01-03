#include "pch.h"

#include "../CSC3221-Project-2/Square.h"
#include "../CSC3221-Project-2/Circle.h"
#include "../CSC3221-Project-2/Shape.h"

TEST(SquareInit, Basic) {
	Square sqr = Square(100);

	ASSERT_EQ(sqr.getLength(), 100);

	ASSERT_EQ(sqr.getX(), 0);
	ASSERT_EQ(sqr.getY(), 0);
}

TEST(SquareInit, Coords) {
	Square sqr = Square(100, 1, 2);

	ASSERT_EQ(sqr.getLength(), 100);

	ASSERT_EQ(sqr.getX(), 1);
	ASSERT_EQ(sqr.getY(), 2);
}

TEST(ShapeCasting, SquareUpCast) {

	Shape* shape = new Square(100);

	ASSERT_EQ(shape->getShapeName(), ShapeTypes::Square);
	ASSERT_EQ(shape->getX(), 0);
	ASSERT_EQ(shape->getY(), 0);

	delete shape;

	Shape* shapeRef = &Square(100);

	ASSERT_EQ(shapeRef->getShapeName(), ShapeTypes::Square);
	ASSERT_EQ(shapeRef->getX(), 0);
	ASSERT_EQ(shapeRef->getY(), 0);
}

TEST(ShapeCasting, CircleUpCast) {

	Shape* shape = &Circle(100);

	ASSERT_EQ(shape->getShapeName(), ShapeTypes::Circle);
	ASSERT_EQ(shape->getX(), 0);
	ASSERT_EQ(shape->getY(), 0);

	Shape* shape2 = new Circle(100);

	ASSERT_EQ(shape2->getShapeName(), ShapeTypes::Circle);
	ASSERT_EQ(shape2->getX(), 0);
	ASSERT_EQ(shape2->getY(), 0);
}

TEST(ShapeCasting, SquareDownCast) {

	Shape* shape = &Square(100);

	// We will use this logic for the collision function, so it's important it actually works

	Square* downCast = static_cast<Square*>(shape);

	ASSERT_EQ(downCast->getShapeName(), ShapeTypes::Square);
	ASSERT_EQ(downCast->getX(), 0);
	ASSERT_EQ(downCast->getY(), 0);
	ASSERT_EQ(downCast->getLength(), 100); // This is the big one, make sure we can get the length from "Shape"

}

TEST(ShapeCasting, CircleDownCast) {

	Shape* shape = &Circle(100);

	// We will use this logic for the collision function, so it's important it actually works

	Circle* downCast = static_cast<Circle*>(shape);

	ASSERT_EQ(downCast->getShapeName(), ShapeTypes::Circle);
	ASSERT_EQ(downCast->getX(), 0);
	ASSERT_EQ(downCast->getY(), 0);
	ASSERT_EQ(downCast->getRadius(), 100); // This is the big one, make sure we can get the length from "Shape"

}

TEST(SquareCollide, Basic) {

	// @ Indicates a collision
	// Number indicates a shape

	// 22
	// @2

	// collides

	Shape* s1 = new Square(1);
	Shape* s2 = new Square(2);

	ASSERT_TRUE(s1->collidesWith(s2));

	//  22
	// 122

	// collide

	Shape* s3 = new Square(1, 0, 0);
	Shape* s4 = new Square(2, 1, 0);

	ASSERT_TRUE(s3->collidesWith(s4));

	//  222
	//  222
	// 1@22
	// 11  

	// collides
	Shape* s5 = new Square(2, 0, 0);
	Shape* s6 = new Square(3, 1, 1);

	ASSERT_TRUE(s5->collidesWith(s6));

	//   22
	//   22
	// 11
	// 11  

	// collide
	Shape* s7 = new Square(2, 0, 0);
	Shape* s8 = new Square(2, 2, 2);

	ASSERT_TRUE(s7->collidesWith(s8));

	// 11 22
	// 11 22 

	// no collide
	Shape* s9 = new Square(2, 0, 0);
	Shape* s10 = new Square(2, 3, 0);

	ASSERT_FALSE(s9->collidesWith(s10));
}

TEST(CircleCollide, Basic) {

	// For circles they don't quite fill the grid correctly
	// I plotted the results on https://www.math10.com/en/geometry/geogebra/geogebra.html
	// to see if they overlap

	// collide
	Shape* s1 = new Circle(1, 1, 1);
	Shape* s2 = new Circle(1, 2, 2);
	ASSERT_TRUE(s1->collidesWith(s2));

	// collide
	Shape* s3 = new Circle(1, 1, 1);
	Shape* s4 = new Circle(1, 3, 1);
	ASSERT_TRUE(s3->collidesWith(s4));

	// no collide
	Shape* s5 = new Circle(1, 1, 1);
	Shape* s6 = new Circle(1, 4, 1);
	ASSERT_FALSE(s5->collidesWith(s6));

	// no collide
	Shape* s7 = new Circle(1, 1, 1);
	Shape* s8 = new Circle(1, 4, 1);
	ASSERT_FALSE(s7->collidesWith(s8));

	// no collide
	// this example shows that they aren't just treated as rectangles, as the corners share a box, this shows that they are treated as circles
	Shape* s9 = new Circle(1, 1, 1);
	Shape* s10 = new Circle(3, 4, 4);
	ASSERT_FALSE(s9->collidesWith(s10));

	// no collide
	// If the radius was bigger in the last one they would overlap
	Shape* s11 = new Circle(2, 1, 1);
	Shape* s12 = new Circle(3, 4, 4);
	ASSERT_TRUE(s11->collidesWith(s12));


}

TEST(SquareCircleColide, Basic) {

	// For circles they don't quite fill the grid correctly
	// I plotted the results on https://www.math10.com/en/geometry/geogebra/geogebra.html
	// to see if they overlap

	// collide
	// Circle and square next to each other, just touching
	Shape* s1 = new Circle(1, 1, 1);
	Shape* s2 = new Square(2, 2, 0);
	ASSERT_TRUE(s1->collidesWith(s2));

	// No Collide
	// Circle and square next to each other, with a gap
	Shape* s3 = new Circle(1, 1, 1);
	Shape* s4 = new Square(2, 3, 0);
	ASSERT_FALSE(s3->collidesWith(s4));

	// Collide
	// Circle happily sat inside the square
	Shape* s5 = new Circle(1, 2, 2);
	Shape* s6 = new Square(5, 0, 0);
	ASSERT_TRUE(s5->collidesWith(s6));

	// Collide
	Shape* s7 = new Square(3, 0, 1);
	Shape* s8 = new Circle(2, 2, 2);
	ASSERT_TRUE(s7->collidesWith(s8));
}