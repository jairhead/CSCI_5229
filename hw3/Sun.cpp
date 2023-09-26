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

// scale() member function
// Sets the rectangular prism's scaling values
void Sun::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() member function
// Sets the rectangular prism's coordinate values
void Sun::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() member function
// Sets the rectangular prism's color values
void Sun::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// draw() member function
// Contains logic to draw the sun
void Sun::draw() {
  // Save transformation and set up
}