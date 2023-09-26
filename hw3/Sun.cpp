/*
 * File: Sun.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Sun class, a child
 *              class of the BaseObject abstract class.
 */

#include "Sun.h"

// Constructor
Sun::Sun() { }

// Destructor
Sun::~Sun() { }

// scale() public member function
// Sets the sun's scaling values
void Sun::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() public member function
// Sets the sun's coordinate values
void Sun::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the sun's color values
void Sun::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// rotate() public member function
// Sets the initial angle for drawing the sun's rays
void Sun::rotate(double th) {
  theta = th;
}

// draw() public member function
// Contains logic to draw the sun
void Sun::draw() {
  // Save transformation, set color, translate and rotate
  glPushMatrix();
  glColor3d(red, green, blue);
  glTranslated(xPos, yPos, zPos);
  glRotated(90, 1, 0, 0);

  // Draw the disc of the sun
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0, 0, 0);
  for (int th = 0; th <= 360; th += d) {
    glVertex3d(xScaling * cosine(th), 0, zScaling * sine(th));
  }
  glEnd();

  // Draw the sun rays  
  for (int th = theta; th <= 360; th += 30) {
    glBegin(GL_TRIANGLES);
    glVertex3d((xScaling + 0.05) * cosine(th), 0, (zScaling + 0.05) * sine(th));
    glVertex3d((xScaling + 0.2) * cosine(th + 2), 0, (zScaling + 0.2) * sine(th + 2));
    glVertex3d((xScaling + 0.2) * cosine(th - 2), 0, (zScaling + 0.2) * sine(th - 2));
    glEnd();
  }

  // Undo transformations
  glPopMatrix();
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double Sun::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Sun::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
