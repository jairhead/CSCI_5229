/*
 * File: Sphere.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Sphere class, a child class
 *              of the BaseObject abstract class.
 */

#include "Sphere.h"

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
  vertex(0, -90);
  for (int th = 0; th <= 360; th += d) { vertex(th, d - 90); }
  glEnd();

  // Draw latitude bands
  for (int ph = d - 90; ph <= 90 - (2 * d); ph += d) {
    glBegin(GL_QUAD_STRIP);
    for (int th = 0; th <= 360; th += d) {
      vertex(th, ph);
      vertex(th, ph + d);
    }
    glEnd();
  }

  // Draw north cap
  glBegin(GL_TRIANGLE_FAN);
  vertex(0, 90);
  for (int th = 0; th <= 360; th += d) { vertex(th, 90 - d); }
  glEnd();

  // Pop transformation
  glPopMatrix();
}

// vertex() private member function
// Draws a triangle with th and ph
void Sphere::vertex(double th, double ph) {
  glColor3f(cosine(th) * cosine(th), sine(ph) * sine(ph), sine(th) * sine(th));
  glVertex3d(sine(th) * cosine(ph), sine(ph), cosine(th) * cosine(ph));
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double Sphere::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Sphere::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
