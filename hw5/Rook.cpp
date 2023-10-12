/*
 * File: Pawn.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Rook class, a child class
 *              of the BaseObject abstract class.
 */

#include "Rook.h"

// Default Constructor
Rook::Rook() {
  scaleArray[0] = 0.35;
  scaleArray[1] = 0.35;
  scaleArray[2] = 0.35;
}

// Destructor
Rook::~Rook() { }

// color() public member function
// Sets the object's color values
void Rook::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
  shinyFactor = 1.0;
}

// draw() public member function
// Contains logic to draw the object
void Rook::draw() {
  // Set material properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
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
  yVal1 = 0.50; yVal2 = 1.80;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 4.399;

  // Tall middle section
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.55; xVal2 = 0.75;
  yVal1 = 1.80; yVal2 = 1.95;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = -53.13;

  // Top section (bottom)
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.75; xVal2 = 0.75;
  yVal1 = 1.95; yVal2 = 2.55;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 0.0;

  // Top section (middle)
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, xVal1 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.75; xVal2 = 0.75;
  yVal1 = 2.55; yVal2 = yVal1;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 0.0;

  // Collar (top)
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0.0, yVal1, 0.0);
  if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
  for (int th = 0; th <= 360; th += d) {
    glVertex3d(xVal1 * cosine(th), yVal1, zVal1 * sine(th));
  }
  glEnd();

  // Adjust xyz tracking values
  xVal1 = 0.75; xVal2 = 0.55;
  yVal1 = 2.55; yVal2 = 2.75;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 0.0;

  // Top section (battlements)
  for (int th = 0; th <= 360; th += 2*d) {
    // Outside of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th), 0.0, sine(th));}
    glVertex3d(xVal1 * cosine(th), yVal1, zVal1 * sine(th)); // bottom point
    glVertex3d(xVal1 * cosine(th), yVal2, zVal1 * sine(th)); // top point
    glVertex3d(xVal1 * cosine(th + d), yVal2, zVal1 * sine(th + d)); // top point
    glVertex3d(xVal1 * cosine(th + d), yVal1, zVal1 * sine(th + d)); // bottom point
    glEnd();

    // Inside of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th + 180.0), 0.0, sine(th + 180.0));}
    glVertex3d(xVal2 * cosine(th), yVal1, zVal2 * sine(th)); // bottom point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
    glVertex3d(xVal2 * cosine(th + d), yVal2, zVal2 * sine(th + d)); // top point
    glVertex3d(xVal2 * cosine(th + d), yVal1, zVal2 * sine(th + d)); // bottom point
    glEnd();

    // Left side of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th - 90.0), 0.0, sine(th - 90.0));}
    glVertex3d(xVal1 * cosine(th), yVal1, zVal1 * sine(th)); // bottom point
    glVertex3d(xVal1 * cosine(th), yVal2, zVal1 * sine(th)); // top point
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
    glVertex3d(xVal2 * cosine(th), yVal1, zVal2 * sine(th)); // bottom point
    glEnd();

    // Right side of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th + 90.0), 0.0, sine(th + 90.0));}
    glVertex3d(xVal1 * cosine(th + d), yVal1, zVal1 * sine(th + d)); // bottom point
    glVertex3d(xVal1 * cosine(th + d), yVal2, zVal1 * sine(th + d)); // top point
    glVertex3d(xVal2 * cosine(th + d), yVal2, zVal2 * sine(th + d)); // top point
    glVertex3d(xVal2 * cosine(th + d), yVal1, zVal2 * sine(th + d)); // bottom point
    glEnd();

    // Top of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
    glVertex3d(xVal1 * cosine(th), yVal2, zVal1 * sine(th)); // left outer
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // left inner
    glVertex3d(xVal2 * cosine(th + d), yVal2, zVal2 * sine(th + d)); // right inner
    glVertex3d(xVal1 * cosine(th + d), yVal2, zVal1 * sine(th + d)); // right outer
    glEnd();
  }

  // End
  glPopMatrix();
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double Rook::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Rook::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
