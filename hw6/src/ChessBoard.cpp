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

  rimRight = new RectangularPrism();
  rimLeft = new RectangularPrism();
  rimFront = new RectangularPrism();
  rimBack = new RectangularPrism();
}

// Destructor
ChessBoard::~ChessBoard() { }

// setTextureFactor() public member function
// Sets the texture factor (scaling) for each of the rectangular prisms
void ChessBoard::setTextureFactor(float tf) {
  blackSquare1->setTextureFactor(tf);
  blackSquare2->setTextureFactor(tf);
  whiteSquare1->setTextureFactor(tf);
  whiteSquare2->setTextureFactor(tf);
}

// setTexture() public overloaded member function
// Sets the texture of the chess board
void ChessBoard::setTexture(unsigned int *tex) {
  blackSquare1->setTexture(tex);
  blackSquare2->setTexture(tex);
  whiteSquare1->setTexture(tex);
  whiteSquare2->setTexture(tex);
}

// setRimTexture() public overloaded member function
// Sets the texture of the chess board rim
void ChessBoard::setRimTexture(unsigned int *tex) {
  rimRight->setTexture(tex);
  rimLeft->setTexture(tex);
  rimFront->setTexture(tex);
  rimBack->setTexture(tex);
}

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

  // Draw Rim Right
  rimRight->translate(1.0, 0.0, 0.0);
  rimRight->scale(0.5, 0.5, 1.50);
  rimRight->draw();

  // Draw Rim Left
  rimLeft->translate(-1.0, 0.0, 0.0);
  rimLeft->scale(0.5, 0.5, 1.50);
  rimLeft->draw();

  // Draw Rim Front
  rimFront->translate(0.0, 0.0, 1.0);
  rimFront->scale(0.5, 0.5, 1.325);
  rimFront->rotate(90.0);
  rimFront->draw();

  // Draw Rim Back
  rimBack->translate(0.0, 0.0, -1.0);
  rimBack->scale(0.5, 0.5, 1.325);
  rimBack->rotate(90.0);
  rimBack->draw();
}
