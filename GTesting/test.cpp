#include "pch.h"

#include "../CSC3221-Project-2/Square.h"

TEST(SquareInit, Basic) {
	Square sqr = Square(100, 200);

	ASSERT_EQ(sqr.getHeight(), 100);
	ASSERT_EQ(sqr.getWidth(), 200);

	ASSERT_EQ(sqr.getX(), 0);
	ASSERT_EQ(sqr.getY(), 0);
}