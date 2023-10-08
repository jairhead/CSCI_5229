/*
 * File: RectangularPrism.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the RectangularPrism class, a child class
 *              of the BaseObject abstract class.
 */

#include "RectangularPrism.h"

// Default Constructor
RectangularPrism::RectangularPrism() { }

// Destructor
RectangularPrism::~RectangularPrism() { }

// color() public member function
// Sets the object's color values
void RectangularPrism::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// draw() public member function
// Contains logic to draw the object
void RectangularPrism::draw() {
  // Save transformation and set up
  glPushMatrix();

  // Translate -> Rotate -> Scale
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);
  glScaled(xScaling, yScaling, zScaling);
  glBegin(GL_QUADS);
  glColor3d(red, green, blue);

  // Front face
  if (lightingEnabled) {glNormal3d(0.0, 0.0, 1.0);}
  glVertex3d(-0.5 * xScaling, -0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, -0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, +0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, +0.5 * yScaling, +0.5 * zScaling);

  // Back face
  if (lightingEnabled) {glNormal3d(0.0, 0.0, -1.0);}
  glVertex3d(+0.5 * xScaling, -0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, -0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, +0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, +0.5 * yScaling, -0.5 * zScaling);

  // Right face
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(+0.5 * xScaling, -0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, -0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, +0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, +0.5 * yScaling, +0.5 * zScaling);

  // Left face
  if (lightingEnabled) {glNormal3d(-1.0, 0.0, 0.0);}
  glVertex3d(-0.5 * xScaling, -0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, -0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, +0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, +0.5 * yScaling, -0.5 * zScaling);

  // Top face
  if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
  glVertex3d(-0.5 * xScaling, +0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, +0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, +0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, +0.5 * yScaling, -0.5 * zScaling);

  // Bottom face
  if (lightingEnabled) {glNormal3d(0.0, -1.0, 0.0);}
  glVertex3d(-0.5 * xScaling, -0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, -0.5 * yScaling, -0.5 * zScaling);
  glVertex3d(+0.5 * xScaling, -0.5 * yScaling, +0.5 * zScaling);
  glVertex3d(-0.5 * xScaling, -0.5 * yScaling, +0.5 * zScaling);

  // End
  glEnd();
  glPopMatrix();
}
