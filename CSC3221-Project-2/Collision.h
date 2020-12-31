#pragma once
#include "Square.h"
#include "Circle.h"
#include <iostream>

#ifndef MY_FOO_HEADER_
#define MY_FOO_HEADER_


bool squareCollision(Square* lhs, Square* rhs);

bool circleCollision(Circle* lhs, Circle* rhs);

bool squareCircleCollision(Square* lhs, Circle* rhs);

#endif