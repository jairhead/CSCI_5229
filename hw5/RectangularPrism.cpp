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
void RectangularPrism::color(float r, float g, float b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
}

// scale() public member function
// Sets the object's scaling values
void RectangularPrism::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// draw() public member function
// Contains logic to draw the object
void RectangularPrism::draw() {
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
  glScaled(xScaling, yScaling, zScaling);
  glBegin(GL_QUADS);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

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
