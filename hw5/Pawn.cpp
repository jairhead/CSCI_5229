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
  scaleArray[0] = 0.3;
  scaleArray[1] = 0.3;
  scaleArray[2] = 0.3;
}

// Destructor
Pawn::~Pawn() { }

// color() public member function
// Sets the object's color values
void Pawn::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
  shinyFactor = 0.5;
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
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Base bottom (circle)
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0.0, 0.0, 0.0);
  if (lightingEnabled) {glNormal3d(0.0, 0.0, -1.0);}
  for (int th = 0; th <= 360; th += d) {
    glVertex3d(cosine(th), 0.0, sine(th));
  }
  glEnd();

  // Declare xyz tracking values
  double xVal1 = 1.00; double xVal2 = 1.00;
  double yVal1 = 0.00; double yVal2 = 0.20;
  double zVal1 = 1.00; double zVal2 = 1.00;
  double ph = 0.00;

  // Base perimeter
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    double ph = 0.0;
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, zVal1 * sine(th));
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th));
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 1.00; xVal2 = 0.95;
  yVal1 = 0.20; yVal2 = 0.30;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 26.565;

  // Slanted base section 1
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.95; xVal2 = 0.65;
  yVal1 = 0.30; yVal2 = 0.50;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 56.31;

  // Slanted base section 2
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.65; xVal2 = 0.55;
  yVal1 = 0.50; yVal2 = 0.70;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 26.565;

  // Slanted base section 3
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.55; xVal2 = 0.40;
  yVal1 = 0.70; yVal2 = 0.80;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 5.711;

  // Slanted base section 4
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.40; xVal2 = 0.30;
  yVal1 = 0.80; yVal2 = 1.80;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 56.31;

  // Tall middle section
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.30; xVal2 = 0.45;
  yVal1 = 1.80; yVal2 = 1.85;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = -71.565;

  // Collar (bottom)
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.45; xVal2 = 0.45;
  yVal1 = 1.85; yVal2 = yVal1;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 71.565;

  // Collar (top)
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0.0, yVal1, 0.0);
  if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
  for (int th = 0; th <= 360; th += d) {
    glVertex3d(xVal1 * cosine(th), yVal1, zVal1 * sine(th));
  }
  glEnd();

  // Top sphere
  yVal1 = 2.25;
  top->translate(0.0, yVal1, 0.0);
  top->color(colorArray[0], colorArray[1], colorArray[2]);
  top->scale(0.45, 0.45, 0.45);
  top->draw();

  // End
  glPopMatrix();
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double Pawn::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Pawn::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
