/*
 * File: AnalogClock.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the AnalogClock class, a child
 *              class of the BaseObject abstract class.
 */

#include "AnalogClock.h"

// Constructor
AnalogClock::AnalogClock() { }

// Destructor
AnalogClock::~AnalogClock() { }

// color() public member function
// Sets the object's color values
void AnalogClock::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
  shinyFactor = 1.0;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the pawn
void AnalogClock::setTextureFactor(float tf) {texFact = tf;}

// setTexture() public overloaded member function
// Sets the texture of the pawn
void AnalogClock::setTexture(unsigned int *tex) {texture = tex;}

// draw() public member function
// Contains logic to draw the object
void AnalogClock::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
  }

  // Save transformation, Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Draw the clock face
  drawFace(1.0, 0.1, 1.0);

  // End
  glPopMatrix();
}

// drawFace() protected member function
// Contains logic to draw the clock face
void AnalogClock::drawFace(double r, double y, double yNorm) {
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(0.0, yNorm, 0.0);}

    // Draw middle vertex
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(0.0, y, 0.0);

    // Draw outer right vertex
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(r * cosine(th), y, r * sine(th));

    // Draw outer left vertex
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(r * cosine(th + d), y, r * sine(th + d));
    glEnd();
  }
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double AnalogClock::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double AnalogClock::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
