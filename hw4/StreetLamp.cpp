/*
 * File: StreetLamp.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the StreetLamp class, a child
 *              class of the BaseObject abstract class.
 */

#include "StreetLamp.h"

// Constructor
StreetLamp::StreetLamp() {
  pole = new RectangularPrism();
  cantilever = new RectangularPrism();
  lamp = new RectangularPrism();
}

// Destructor
StreetLamp::~StreetLamp() { }

// translate() public member function
// Sets the street lamp's coordinate values
void StreetLamp::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the street lamp's colors
void StreetLamp::color(bool day) {
  if (day) {
    dayTime = true;
    poleC[0][0] = poleC[1][0];
    poleC[0][1] = poleC[1][1];
    poleC[0][2] = poleC[1][2];
  }
  else {
    dayTime = false;
    poleC[0][0] = poleC[2][0];
    poleC[0][1] = poleC[2][1];
    poleC[0][2] = poleC[2][2];
  }
}

// rotate() public member function
// Sets the angle for drawing the street lamp
void StreetLamp::rotate(double th) {
  theta = th;
}

// draw()
// Contains logic to draw a street lamp
void StreetLamp::draw() {
  // Save transformation, translate and rotate
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);

  // Draw the pole
  pole->color(poleC[0][0], poleC[0][1], poleC[0][2]);
  pole->scale(0.01, 0.2, 0.01);
  pole->translate(0.0, 0.2, 0.0);
  pole->draw();

  // Draw the cantilever
  cantilever->color(poleC[0][0], poleC[0][1], poleC[0][2]);
  cantilever->translate(0.08, 0.4, 0.0);
  cantilever->scale(0.08, 0.01, 0.01);
  cantilever->draw();

  // Draw the lamp
  lamp->color(poleC[0][0], poleC[0][1], poleC[0][2]);
  lamp->translate(0.16, 0.4, 0.0);
  lamp->scale(0.03, 0.01, 0.03);
  lamp->draw();

  // If it's night, draw the light on the ground
  if (!dayTime) {
    glColor3d(lightC[0][0], lightC[0][1], lightC[0][2]);
    glTranslated(0.16, yPos + 0.03, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0, 0, 0);
    for (int th = 0; th <= 360; th += d) {
      glVertex3d(0.15 * cosine(th), 0, 0.15 * sine(th));
    }
    glEnd();
  }

  // Undo transformations
  glPopMatrix();
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double StreetLamp::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double StreetLamp::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
