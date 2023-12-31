/*
 * File: Cube.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Cube class, a child class
 *              of the BaseObject abstract class.
 */

#include "Cube.h"

// Default Constructor
Cube::Cube() { }

// Overloaded Constructor
Cube::Cube(double x, double y, double z,
           double dx, double dy, double dz,
           double th) {
  xPos = x;
  yPos = y;
  zPos = z;
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
  theta = th;
}

// Destructor
Cube::~Cube() { }

// draw() member function
// Contains logic to draw the cube
void Cube::draw() {
  // Save transformation and set up
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);
  glScaled(xScaling, yScaling, zScaling);
  glBegin(GL_QUADS);

  // Front face
  glColor3f(1,0,0);
  glVertex3f(-1,-1, 1);
  glVertex3f(+1,-1, 1);
  glVertex3f(+1,+1, 1);
  glVertex3f(-1,+1, 1);

  // Back face
  glColor3f(0,0,1);
  glVertex3f(+1,-1,-1);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,+1,-1);
  glVertex3f(+1,+1,-1);

  // Right face
  glColor3f(1,1,0);
  glVertex3f(+1,-1,+1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,+1,-1);
  glVertex3f(+1,+1,+1);

  // Left face
  glColor3f(0,1,0);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,-1,+1);
  glVertex3f(-1,+1,+1);
  glVertex3f(-1,+1,-1);

  // Top face
  glColor3f(0,1,1);
  glVertex3f(-1,+1,+1);
  glVertex3f(+1,+1,+1);
  glVertex3f(+1,+1,-1);
  glVertex3f(-1,+1,-1);

  // Bottom face
  glColor3f(1,0,1);
  glVertex3f(-1,-1,-1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,-1,+1);
  glVertex3f(-1,-1,+1);

  // End and pop transformation
  glEnd();
  glPopMatrix();
}
