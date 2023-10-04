/*
 * File: Cloud.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Cloud class, a child
 *              class of the BaseObject abstract class.
 */

#include "Tree.h"

// Constructor
Tree::Tree() {
  leaves = new Sphere(0.0, 0.15, 0.0, 0.1, 0.0);
  trunk = new RectangularPrism();
}

// Destructor
Tree::~Tree() { }

// translate() public member function
// Sets the tree's coordinate values
void Tree::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the tree's colors
void Tree::color(bool day) {
  if (day) {
    dayTime = true;
    leavesC[0][0] = leavesC[1][0];
    leavesC[0][1] = leavesC[1][1];
    leavesC[0][2] = leavesC[1][2];
    trunkC[0][0] = trunkC[1][0];
    trunkC[0][1] = trunkC[1][1];
    trunkC[0][2] = trunkC[1][2];
  }
  else {
    dayTime = false;
    leavesC[0][0] = leavesC[2][0];
    leavesC[0][1] = leavesC[2][1];
    leavesC[0][2] = leavesC[2][2];
    trunkC[0][0] = trunkC[2][0];
    trunkC[0][1] = trunkC[2][1];
    trunkC[0][2] = trunkC[2][2];
  }
}

// rotate() public member function
// Sets the angle for drawing the tree
void Tree::rotate(double th) {
  theta = th;
}

// draw()
// Contains logic to draw a tree
void Tree::draw() {
  // Save transformation, translate and rotate
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);

  // Draw the leaves
  leaves->translate(0.0, 0.3, 0.0);
  leaves->color(leavesC[0][0], leavesC[0][1], leavesC[0][2]);
  leaves->draw();

  // Draw the trunk
  trunk->color(trunkC[0][0], trunkC[0][1], trunkC[0][2]);
  trunk->translate(0.0, 0.15, 0.0);
  trunk->scale(0.015, 0.15, 0.015);
  trunk->draw();

  // Undo transformations
  glPopMatrix();
}
