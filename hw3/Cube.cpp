/*
 * File: Cube.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Cube class
 */

#include "Cube.h"

// Globals
double xPos = 0.0;
double yPos = 0.0;
double zPos = 0.0;
double theta = 0.0;

// Constructor
Cube::Cube(double x, double y, double z, double th) {
  xPos = x;
  yPos = y;
  zPos = z;
  theta = th;
}

// Destructor
Cube::~Cube() { }

// display() member function
// Contains logic to display the cube
void Cube::display() {
  // Save transformation and set up
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);
  glScaled(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);

  // Front face
  glColor3f(1,0,0);
  glVertex3f(-1,-1, 1);
  glVertex3f(+1,-1, 1);
  glVertex3f(+1,+1, 1);
  glVertex3f(-1,+1, 1);

  // End and pop transformation
  glEnd();
  glPopMatrix();
}