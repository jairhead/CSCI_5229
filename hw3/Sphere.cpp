/*
 * File: Sphere.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Sphere class, a child class
 *              of the BaseObject abstract class.
 */

 #include "Sphere.h"

// Globals
double scalingFactor;
const int d = 15;

// Default Constructor
Sphere::Sphere() { }

// Overloaded Constructor
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

  // Draw south cap
  glBegin(GL_TRIANGLE_FAN);
  Vertex(0, -90);
  for (int th = 0; th <= 360; th += d) { Vertex(th, d - 90); }
  glEnd();

  // Draw latitude bands
  for (int ph = d - 90; ph <= 90 - (2 * d); ph += d) {
    glBegin(GL_QUAD_STRIP);
    for (int th = 0; th <= 360; th += d) {
      Vertex(th, ph);
      Vertex(th, ph + d);
    }
    glEnd();
  }

  // Draw north cap
  glBegin(GL_TRIANGLE_FAN);
  Vertex(0, 90);
  for (int th = 0; th <= 360; th += d) { Vertex(th, 90 - d); }
  glEnd();

  // Pop transformation
  glPopMatrix();
}
