/*
 * File: Moon.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Moon class, a child
 *              class of the BaseObject abstract class.
 */

#include "Moon.h"

// Constructor
Moon::Moon() { }

// Destructor
Moon::~Moon() { }

// scale() public member function
// Sets the moon's scaling values
void Moon::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() public member function
// Sets the moon's coordinate values
void Moon::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the moon's color values
void Moon::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// rotate() public member function
// Sets the initial angle for drawing the moon's rays
void Moon::rotate(double th) {
  theta = th;
}

// draw() public member function
// Contains logic to draw the moon
void Moon::draw() {
  // Save transformation, set color, translate and rotate
  glPushMatrix();
  glColor3d(red, green, blue);
  glTranslated(xPos, yPos, zPos);
  glRotated(90.0, 1, 0, 0);
  glRotated(108.0, 0, 1, 0);

  // Draw the moon
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d((xScaling * 0.9), 0.0, (zScaling * 0.9));
  glVertex3d(0.0, 0.0, (zScaling * 0.85));
  glVertex3d(-(xScaling * 0.8), 0.0, (zScaling * 1.5));
  glVertex3d(0.0, 0.0, 0.0);
  glEnd();

  // Undo transformations
  glPopMatrix();
}
