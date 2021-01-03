#pragma once

#include "Shape.h"
#include <vector>

class Game {

public:

	/**
	 * @brief Constructor for a new Game
	 * @param numberSquares
	 * @param numberCircles
	 * @param shapeMaxSize - Create new shapes with this as max length/radius
	 * @param size - game board size
	*/
	Game(int numberSquares, int numberCircles, int shapeMaxSize, int size);

	/**
	 * @brief Perform a game step (move forwards one step)
	 * @param size
	 * @return
	*/
	void step(int stepMax);

	/**
	 * @brief Print current content of the game
	*/
	void printContent();

	/**
	 * @brief Run through the game until one left, print + remove collisions as we go
	*/
	void play();

private:

	/**
	 * @brief Add new shape to the gamestate
	 * @param type
	 * @param shapeMaxSize
	*/
	void addShape(ShapeTypes type, int shapeMaxSize);

	/**
	 * @brief Helper function to get shape bounds
	 * @param shape
	 * @return
	*/
	int* getShapeBounds(Shape& shape);

	/**
	 * @brief Helper function to get shape bounds
	*/
	int* getShapeBounds(ShapeTypes type, int shapeSize);

	/**
	 * @brief Print and remove and collisions in the visiting game state
	*/
	void collidePurge();

	vector<Shape*> gameState;

	int numberSquares, numberCircles, shapeMaxSize, size;

};

