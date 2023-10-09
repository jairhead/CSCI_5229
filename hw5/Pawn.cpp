/*
 * File: Pawn.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Pawn class, a child class
 *              of the BaseObject abstract class.
 */

#include "Pawn.h"

// Default Constructor
Pawn::Pawn() {
  top = new Sphere();
  scaleArray[0] = 0.6;
  scaleArray[1] = 0.6;
  scaleArray[2] = 0.6;
}

// Destructor
Pawn::~Pawn() { }

// color() public member function
// Sets the object's color values
void Pawn::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
}

// draw() public member function
// Contains logic to draw the object
void Pawn::draw() {
  // Set material properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
  }

  // Save transformation and set up
  glPushMatrix();

  // Translate -> Rotate -> Scale
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Base bottom (circle)
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0.0, 0.0, 0.0);
  if (lightingEnabled) {glNormal3d(0.0, 0.0, -1.0);}
  for (int th = 0; th <= 360; th += d) {
    glVertex3d(scaleArray[0] * cosine(th), 0.0, scaleArray[2] * sine(th));
  }
  glEnd();

  // Base perimeter

  // End
  glPopMatrix();
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double Pawn::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Pawn::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
