/*
 * File: TallGrass.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the TallGrass class, a child
 *              class of the BaseObject abstract class.
 */

#include "TallGrass.h"

// Constructor
TallGrass::TallGrass() { }

// Destructor
TallGrass::~TallGrass() { }

// setTheta() public member function
// Sets the y rotation value theta
void TallGrass::setTheta(double th) {theta = th;}

// setPhi() public member function
// Sets the x rotation value phi
void TallGrass::setPhi(double ph) {phi = ph;}

// draw() public member function
// Contains logic to draw the object
void TallGrass::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
  }

  // Save transformation; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glRotated(phi, 1, 0, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Draw first blade of grass
  glPushMatrix();
  glColor3f(color1[0], color1[1], color1[2]);
  double h = 2.0; double r = 0.1;
  double hyp = Utilities::hypotenuse(r, h);
  double ph = Utilities::arcSine((r)/(hyp));
  drawBlade(h, r, ph);
  glPopMatrix();

  // Draw second blade of grass
  glPushMatrix();
  glTranslated(0.2, 0.0, 0.2);
  glColor3f(color2[0], color2[1], color2[2]);
  h = 2.0; r = 0.1;
  hyp = Utilities::hypotenuse(r, h);
  ph = Utilities::arcSine((r)/(hyp));
  drawBlade(h, r, ph);
  glPopMatrix();

  // Draw second blade of grass
  glPushMatrix();
  glTranslated(-0.2, 0.0, 0.2);
  glColor3f(color2[0], color2[1], color2[2]);
  h = 2.0; r = 0.1;
  hyp = Utilities::hypotenuse(r, h);
  ph = Utilities::arcSine((r)/(hyp));
  drawBlade(h, r, ph);
  glPopMatrix();

  // End
  glPopMatrix();
}

// drawTop() private member function
// Contains logic to draw a blade of grass
void TallGrass::drawBlade(double h, double r, double ph) {
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(Utilities::cosine(th), Utilities::sine(ph), Utilities::sine(th));}

    // Draw middle vertex
    glVertex3d(0.0, h, 0.0);

    // Draw outer right vertex
    glVertex3d(r * Utilities::cosine(th), 0.0, r * Utilities::sine(th));

    // Draw outer left vertex
    glVertex3d(r * Utilities::cosine(th + d), 0.0, r * Utilities::sine(th + d));
    glEnd();
  }
}
