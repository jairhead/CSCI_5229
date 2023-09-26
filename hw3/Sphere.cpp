/*
 * File: Sphere.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Sphere class, a child class
 *              of the BaseObject abstract class.
 */

 #include "Sphere.h"

// Globals
double scalingFactor;

// Default Constructor
Sphere::Sphere() { }

// OVerloaded Constructor
Sphere::Sphere(double x, double y, double z,
               double s, double th) {
  xPos = x;
  yPos = y;
  zPos = z;
  scalingFactor = s;
  theta = th;
}

// Destructor
Sphere::~Sphere() { }

// display() member function
// Contains to display the sphere
void Sphere::draw() {
  // Save transformation and set up
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);
  glScaled(scalingFactor, scalingFactor, scalingFactor);

  // Draw the south pole cap
  glBegin(GL_TRIANGLE_FAN);
  Vertex(0, -90);

  // End and pop transformation
  glEnd();
  glPopMatrix();
}
