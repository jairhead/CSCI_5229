/*
 * File: ChessBoard.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the ChessBoard class, a child class
 *              of the BaseObject abstract class.
 */

#include "ChessBoard.h"

// Default Constructor
ChessBoard::ChessBoard() {
  blackSquare1 = new RectangularPrism();
  blackSquare2 = new RectangularPrism();
  whiteSquare1 = new RectangularPrism();
  whiteSquare2 = new RectangularPrism();
}

// Destructor
ChessBoard::~ChessBoard() { }

// draw() public member function
// Contains logic to draw the object
void ChessBoard::draw() {
  // Draw Black Square 1
  blackSquare1->translate(0.5, 0.0, 0.5);
  blackSquare1->scale(1.0, 0.2, 1.0);
  blackSquare1->color(blackSquareR, blackSquareG, blackSquareB);
  blackSquare1->draw();

  // Draw Black Square 2
  blackSquare2->translate(-0.5, 0.0, -0.5);
  blackSquare2->scale(1.0, 0.2, 1.0);
  blackSquare2->color(blackSquareR, blackSquareG, blackSquareB);
  blackSquare2->draw();

  // Draw White Square 1
  whiteSquare1->translate(0.5, 0.0, -0.5);
  whiteSquare1->scale(1.0, 0.2, 1.0);
  whiteSquare1->color(whiteSquareR, whiteSquareG, whiteSquareB);
  whiteSquare1->draw();

  // Draw White Square 2
  whiteSquare2->translate(-0.5, 0.0, 0.5);
  whiteSquare2->scale(1.0, 0.2, 1.0);
  whiteSquare2->color(whiteSquareR, whiteSquareG, whiteSquareB);
  whiteSquare2->draw();
}
