/*
 * File: House.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the House class, a child
 *              class of the BaseObject abstract class.
 */

#include "House.h"

// Constructor
House::House() { }

// Destructor
House::~House() { }

// scale() public member function
// Sets the house's scaling values
void House::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() public member function
// Sets the house's coordinate values
void House::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the house's wall color values
void House::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// rotate() public member function
// Sets the initial angle for drawing the house
void House::rotate(double th) {
  theta = th;
}

// draw() public member function
// Contains logic to draw the house
void House::draw() {
  // Save transformation, set color, translate and rotate
  glPushMatrix();
  glColor3d(red, green, blue);
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);

  // Front
  glBegin(GL_QUADS);
  glVertex3f(-xScaling, 0, +zScaling);
  glVertex3f(+xScaling, 0, +zScaling);
  glVertex3f(+xScaling, +yScaling, +zScaling);
  glVertex3f(-xScaling, +yScaling, +zScaling);

  // Back
  glVertex3f(+xScaling, 0, -zScaling);
  glVertex3f(-xScaling, 0, -zScaling);
  glVertex3f(-xScaling, +yScaling, -zScaling);
  glVertex3f(+xScaling, +yScaling, -zScaling);

  // Right Side
  glVertex3f(+xScaling, 0, +zScaling);
  glVertex3f(+xScaling, 0, -zScaling);
  glVertex3f(+xScaling, +yScaling, -zScaling);
  glVertex3f(+xScaling, +yScaling, +zScaling);

  // Left Side
  glVertex3f(-xScaling, 0, -zScaling);
  glVertex3f(-xScaling, 0, +zScaling);
  glVertex3f(-xScaling, +yScaling, +zScaling);
  glVertex3f(-xScaling, +yScaling, -zScaling);

  // Bottom
  glVertex3f(-xScaling, 0, -zScaling);
  glVertex3f(+xScaling, 0, -zScaling);
  glVertex3f(+xScaling, 0, +zScaling);
  glVertex3f(-xScaling, 0, +zScaling);
  glEnd();

  // Front Gable
  glBegin(GL_TRIANGLES);
  glVertex3f(+xScaling, +yScaling, +zScaling);
  glVertex3f(0, +yScaling + yScaling * 0.25, +zScaling);
  glVertex3f(-xScaling, +yScaling, +zScaling);
  glEnd();

  // Back Gable
  glBegin(GL_TRIANGLES);
  glVertex3f(+xScaling, +yScaling, -zScaling);
  glVertex3f(0, (+yScaling + yScaling * 0.25), -zScaling);
  glVertex3f(-xScaling, +yScaling, -zScaling);
  glEnd();

  // Right Roof
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3f(+xScaling, +yScaling, +zScaling);
  glVertex3f(0, +yScaling + yScaling * 0.25, +zScaling);
  glVertex3f(0, (+yScaling + yScaling * 0.25), -zScaling);
  glVertex3f(+xScaling, +yScaling, -zScaling);

  // Right Roof
  glVertex3f(-xScaling, +yScaling, +zScaling);
  glVertex3f(0, +yScaling + yScaling * 0.25, +zScaling);
  glVertex3f(0, (+yScaling + yScaling * 0.25), -zScaling);
  glVertex3f(-xScaling, +yScaling, -zScaling);
  glEnd();

  // Front Window
  glColor3d(0.87, 0.77, 0);
  glBegin(GL_QUADS);
  glVertex3f((xScaling * 0.25), (yScaling * 0.25), zScaling + 0.01);
  glVertex3f((xScaling * 0.25) + 0.05, (yScaling * 0.25), zScaling + 0.01);
  glVertex3f((xScaling * 0.25) + 0.05, (yScaling * 0.25) + 0.1, zScaling + 0.01);
  glVertex3f((xScaling * 0.25), (yScaling * 0.25) + 0.1, zScaling + 0.01);
  glEnd();

  // Left Window
  glBegin(GL_QUADS);
  glVertex3f(-(xScaling + 0.01), (yScaling * 0.25) + 0.05, (zScaling * 0.25));
  glVertex3f(-(xScaling + 0.01), (yScaling * 0.25) + 0.05, (zScaling * 0.25) + 0.1);
  glVertex3f(-(xScaling + 0.01), (yScaling * 0.25) + 0.1, (zScaling * 0.25) + 0.1);
  glVertex3f(-(xScaling + 0.01), (yScaling * 0.25) + 0.1, (zScaling * 0.25));
  glEnd();

  // Right Window
  glBegin(GL_QUADS);
  glVertex3f(xScaling + 0.01, (yScaling * 0.25) + 0.05, (zScaling * 0.25));
  glVertex3f(xScaling + 0.01, (yScaling * 0.25) + 0.05, (zScaling * 0.25) - 0.20);
  glVertex3f(xScaling + 0.01, (yScaling * 0.25) + 0.1, (zScaling * 0.25) - 0.20);
  glVertex3f(xScaling + 0.01, (yScaling * 0.25) + 0.1, (zScaling * 0.25));
  glEnd();

  // Undo transformations
  glPopMatrix();
}