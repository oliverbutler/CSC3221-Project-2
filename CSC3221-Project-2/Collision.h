#pragma once
#include "Square.h"
#include "Circle.h"
#include <iostream>

#ifndef MY_FOO_HEADER_
#define MY_FOO_HEADER_

/**
 * @brief Generate a random number between min and max, uses rand() so tends towards 0 as is only pseudo random
 * @param min
 * @param max
 * @return
*/
int genRand(int min, int max);

/**
 * @brief Do two squares collide?
 * @param lhs
 * @param rhs
 * @return
*/
bool squareCollision(Square* lhs, Square* rhs);

/**
 * @brief Do two circles collide?
 * @param lhs
 * @param rhs
 * @return
*/
bool circleCollision(Circle* lhs, Circle* rhs);

/**
 * @brief Does given square and circle collide (slightly more difficult)
 * @param lhs
 * @param rhs
 * @return
*/
bool squareCircleCollision(Square* lhs, Circle* rhs);

#endif