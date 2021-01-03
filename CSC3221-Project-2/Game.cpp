#include "Game.h"
#include "Shape.h"
#include "Square.h"
#include "Circle.h"
#include "Collision.h"
#include <algorithm>
#include <vector>

/**
 * @brief Create a new game given the params, the game space is size*size big. Also then adds the shapes you need
 * @param numberSquares
 * @param numberCircles
 * @param shapeMaxSize
 * @param size
*/
Game::Game(int numberSquares, int numberCircles, int shapeMaxSize, int size) {
	this->numberSquares = numberSquares;
	this->numberCircles = numberCircles;
	this->shapeMaxSize = shapeMaxSize;
	this->size = size;

	for (int i = 0; i < numberSquares; i++)
		addShape(ShapeTypes::Square, shapeMaxSize);

	for (int i = 0; i < numberCircles; i++)
		addShape(ShapeTypes::Circle, shapeMaxSize);

	printContent();

	cout << "\n\n";

}

/**
 * @brief Overall way to start the game, it just loops through until there is only one shape left, and performs the step
*/
void Game::play() {
	int round = 1;
	while (gameState.size() > 1) {
		cout << "[" << round << "] Running... " << gameState.size() << " left \n";
		step(2);
		round++;
	}

}

/**
 * @brief Steps through one iteration of the game, also prints game state + removes any overlapping shapes
 * @param stepMax
*/
void Game::step(int stepMax) {

	int* bounds;

	// Lets move all of the shapes 
	for (int i = 0; i < numberSquares + numberCircles; i++) {
		// The safe bounds (x,y) for a given shape => handy function.
		bounds = getShapeBounds(*gameState[i]);

		// Gets the coords that we WOULD be moving to if we didn't adjust the values
		int targetX = gameState[i]->getX() + genRand(-stepMax, stepMax);
		int targetY = gameState[i]->getY() + genRand(-stepMax, stepMax);

		// Lets ensure that these coords don't go outside the safe bounds of our shape
		int targetXLimited = max(bounds[0], min(targetX, bounds[1]));
		int targetYLimited = max(bounds[2], min(targetY, bounds[3]));

		// Adjusted x+y steps, (these wont allow the shape to go outside the zone, and instead it just is stopped by the wall
		int adjustedXStep = targetXLimited - gameState[i]->getX();
		int adjustedYStep = targetYLimited - gameState[i]->getY();

		gameState[i]->translate(adjustedXStep, adjustedYStep);
	}

	// Print game state
	printContent();

	// Print any collisions + remove them
	collidePurge();
}

/**
 * @brief Print current game state
*/
void Game::printContent() {
	cout << "===> Game Contents <=== \n";
	for (int i = 0; i < gameState.size(); i++) {

		// To print them we need to print the derived (downcasted) shape
		Shape* ref = gameState[i];

		// Do a different downcast based on the shape type
		switch (ref->getShapeName()) {
		case ShapeTypes::Square:
			cout << i << ": " << *static_cast<Square*>(ref) << "\n";
			break;
		case ShapeTypes::Circle:
			cout << i << ": " << *static_cast<Circle*>(ref) << "\n";
			break;
		}
	}
}

/**
 * This method adds a new shape to the game, with the restriction that it wont stick out of the sides
*/
void Game::addShape(ShapeTypes type, int shapeMaxSize) {

	// Create a pointer for this new shape
	Shape* newShapeRef;

	// Find out what random(ish) size it will be
	int shapeSize = genRand(1, shapeMaxSize);
	// use this size (and type) to find the available x + y bounds for this shapes position
	int* bounds = getShapeBounds(type, shapeSize);

	switch (type) {
	case ShapeTypes::Square:
	{
		// Place this new shape within these bounds + size
		newShapeRef = new Square(shapeSize, genRand(bounds[0], bounds[1]), genRand(bounds[2], bounds[3]));
		break;
	}

	case ShapeTypes::Circle:
	{
		// Place this new shape within these bounds + size
		newShapeRef = new Circle(shapeSize, genRand(bounds[0], bounds[1]), genRand(bounds[2], bounds[3]));
		break;
	}

	}

	// Add this new shape to the back of the game state vector
	gameState.push_back(newShapeRef);
}

// Get bounds based off a shape rather than the type + size, handy for when the shape is already created 
int* Game::getShapeBounds(Shape& shape) {
	ShapeTypes type = shape.getShapeName();

	// Shape size
	int size = 0;


	switch (type) {
	case ShapeTypes::Square:
		size = static_cast<Square*>(&shape)->getLength();
		break;
	case ShapeTypes::Circle:
		size = static_cast<Circle*>(&shape)->getRadius();
		break;
	}

	return getShapeBounds(type, size);
}

// Runs through the whole game state and checks for collisions
void Game::collidePurge() {

	cout << "==> Purging Collisions <==\n";

	// Vector we use to store shapes which will be removed
	vector<int> deathRow = {};

	// O(N^2) unfortunately, some optimizations could be performed via Space partitioning, 
	// HOWEVER for this situation where we move ALL of the shapes every 'round' O(N^2) isn't terrible. 
	// Especially for a small population.
	for (int x = 0; x < gameState.size(); x++) {
		for (int y = 0; y < gameState.size(); y++) {
			// Ensure we don't check shape A is colliding with Shape A, because... it will be :)
			// Call our base class' collidesWith function for two shapes
			if (x != y && gameState[x]->collidesWith(gameState[y])) {
				cout << "[" << x << "] + [" << y << "] Collides <- Removed!\n";
				deathRow.push_back(x); // Add these shapes to 'death row'
				deathRow.push_back(y);
			}
		}
	}

	// Sort the array (lets us erase properly)
	sort(deathRow.begin(), deathRow.end());

	// New vector with only the unique elements
	vector<int>::iterator it;
	it = std::unique(deathRow.begin(), deathRow.end());

	// Resize ours to this unique array
	deathRow.resize(distance(deathRow.begin(), it));

	for (int i = gameState.size() - 1; i >= 0; i--) {
		if (binary_search(deathRow.begin(), deathRow.end(), i)) {
			delete gameState[i];
			gameState.erase(gameState.begin() + i);
		}
	}

	cout << "\n\n";
}

/**
 * @brief [0 minX][1 maxX][2 minY][3 maxY]
 * @param type
 * @param shapeSize
 * @return
*/
int* Game::getShapeBounds(ShapeTypes type, int shapeSize) {

	// The logic for this function is, where is the safe boundaries we can place a given 
	// shape to where it WONT overlap the game space? 
	// This solves the problem of us generating a game board which already goes outside the given zone

	// [0 minX][1 maxX][2 minY][3 maxY]
	int bounds[4] = { 0 };

	switch (type) {
	case ShapeTypes::Square:
		bounds[1] = size - shapeSize; // xMax
		bounds[3] = size - shapeSize; // yMax
		break;
	case ShapeTypes::Circle:
		bounds[0] = shapeSize; // xMin
		bounds[1] = size - shapeSize; //xMax
		bounds[2] = shapeSize; // yMin
		bounds[3] = size - shapeSize; // yMax
	}

	return bounds;
}
