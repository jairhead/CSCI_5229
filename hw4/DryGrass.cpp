/*
 * File: DryGrass.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the DryGrass class, a child
 *              class of the BaseObject abstract class.
 */

#include "DryGrass.h"

// Constructor
DryGrass::DryGrass() { }

// Destructor
DryGrass::~DryGrass() { }

// scale() public member function
// Sets the dry grass scaling values
void DryGrass::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() public member function
// Sets the dry grass coordinate values
void DryGrass::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the dry grass color values
void DryGrass::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// rotate() public member function
// Sets the initial angle for drawing the dry grass
void DryGrass::rotate(double th) {
  theta = th;
}

// draw() public member function
// Contains logic to draw the dry grass
void DryGrass::draw() {
  // Save transformation, set color, translate and rotate
  glPushMatrix();
  glColor3d(red, green, blue);
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);

  // First Blade of Grass
  glBegin(GL_TRIANGLES);
  glVertex3f((0.1 * xScaling), 0.0, (0.1 * zScaling));
  glVertex3f((0.12 * xScaling), 0.0, (0.12 * zScaling));
  glVertex3f((0.1 * xScaling), (0.2 * yScaling), (0.1 * zScaling));
  glEnd();

  // Second Blade of Grass
  glRotated(theta + 90, 0, 1, 0);
  glBegin(GL_TRIANGLES);
  glVertex3f((0.1 * xScaling), 0.0, (0.1 * zScaling));
  glVertex3f((0.12 * xScaling), 0.0, (0.12 * zScaling));
  glVertex3f((0.12 * xScaling), (0.2 * yScaling), (0.12 * zScaling));
  glEnd();

  // Third Blade of Grass
  glRotated(theta + 180, 0, 1, 0);
  glBegin(GL_TRIANGLES);
  glVertex3f((0.08 * xScaling), 0.0, (0.08 * zScaling));
  glVertex3f((0.1 * xScaling), 0.0, (0.1 * zScaling));
  glVertex3f((0.08 * xScaling), (0.18 * yScaling), (0.08 * zScaling));
  glEnd();

  // Undo transformations
  glPopMatrix();
}
