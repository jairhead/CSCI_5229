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

// draw() public member function
// Contains logic to draw the object
void RectangularPrism::draw() {
  // Set material properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
  }

  // Save transformation; translate -> rotate -> scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Front face
  glBegin(GL_QUADS);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);
  if (lightingEnabled) {glNormal3d(0.0, 0.0, 1.0);}
  glVertex3d(-0.5 * scaleArray[0], -0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], -0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], +0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], +0.5 * scaleArray[1], +0.5 * scaleArray[1]);

  // Back face
  if (lightingEnabled) {glNormal3d(0.0, 0.0, -1.0);}
  glVertex3d(+0.5 * scaleArray[0], -0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], -0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], +0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], +0.5 * scaleArray[1], -0.5 * scaleArray[1]);

  // Right face
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(+0.5 * scaleArray[0], -0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], -0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], +0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], +0.5 * scaleArray[1], +0.5 * scaleArray[1]);

  // Left face
  if (lightingEnabled) {glNormal3d(-1.0, 0.0, 0.0);}
  glVertex3d(-0.5 * scaleArray[0], -0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], -0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], +0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], +0.5 * scaleArray[1], -0.5 * scaleArray[1]);

  // Top face
  if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
  glVertex3d(-0.5 * scaleArray[0], +0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], +0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], +0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], +0.5 * scaleArray[1], -0.5 * scaleArray[1]);

  // Bottom face
  if (lightingEnabled) {glNormal3d(0.0, -1.0, 0.0);}
  glVertex3d(-0.5 * scaleArray[0], -0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], -0.5 * scaleArray[1], -0.5 * scaleArray[1]);
  glVertex3d(+0.5 * scaleArray[0], -0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glVertex3d(-0.5 * scaleArray[0], -0.5 * scaleArray[1], +0.5 * scaleArray[1]);
  glEnd();

  // Undo transformations
  glPopMatrix();
}
