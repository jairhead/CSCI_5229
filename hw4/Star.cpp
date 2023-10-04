/*
 * File: Star.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Star class, a child
 *              class of the BaseObject abstract class.
 */

#include "Star.h"

// Constructor
Star::Star() { }

// Destructor
Star::~Star() { }

// scale() public member function
// Sets the star's scaling values
void Star::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() public member function
// Sets the star's coordinate values
void Star::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the star's color values
void Star::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// rotate() public member function
// Sets the initial angle for drawing the star
void Star::rotate(double th) {
  theta = th;
}

// draw() public member function
// Contains logic to draw the star
void Star::draw() {
  // Save transformation, set color, translate and rotate
  glPushMatrix();
  glColor3d(red, green, blue);
  glTranslated(xPos, yPos, zPos);
  glRotated(90.0, 1, 0, 0);
  glRotated(theta, 0, 1, 0);

  // Draw the star
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d((0.1 * xScaling), 0.0, (0.1 * zScaling));
  glVertex3d(xScaling, 0.0, 0.0);
  glVertex3d((0.1 * xScaling), 0.0, -(0.1 * zScaling));
  glVertex3d(0.0, 0.0, -zScaling);
  glVertex3d(-(0.1 * xScaling), 0.0, -(0.1 * zScaling));
  glVertex3d(-xScaling, 0.0, 0.0);
  glVertex3d(-(0.1 * xScaling), 0.0, (0.1 * zScaling));
  glVertex3d(0.0, 0.0, zScaling);
  glVertex3d((0.1 * xScaling), 0.0, (0.1 * zScaling));
  glEnd();

  // Undo transformations
  glPopMatrix();
}
